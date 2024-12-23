#! /usr/bin/env python3

import shutil
import argparse
import os
from pathlib import Path
from typing import Dict, List, Set, Union
import subprocess

import ninja_syntax
import splat
import splat.scripts.split as split
from splat.segtypes.linker_entry import LinkerEntry

ROOT = Path(__file__).parent.resolve()

YAML_FILE = "splat.yaml"
BASENAME = "mariotennis"
LD_PATH = f"{BASENAME}.ld"
MAP_PATH = f"build/{BASENAME}.map"
ELF_PATH = f"build/{BASENAME}.elf"
Z64_PATH = f"build/{BASENAME}.z64"
OK_PATH = f"build/{BASENAME}.ok"

COMMON_INCLUDES = "-I include -I ultralib/include "

CROSS = "mips-linux-gnu-"
CROSS_AS = f"{CROSS}as"
CROSS_LD = f"{CROSS}ld"
CROSS_STRIP = f"{CROSS}strip"
CROSS_OBJCOPY = f"{CROSS}objcopy"

CC_DIR = "tools/cc"
CC = f"{CC_DIR}/gcc"
AS = f"{CC_DIR}/gcc -x assembler-with-cpp"
CFLAGS = "-nostdinc -mips2 -O3 -g0 -G0 -c -Wall"
GAME_CC_CMD = f"{CC} {CFLAGS} {COMMON_INCLUDES} -D_LANGUAGE_C -DBUILD_VERSION=VERSION_K -D_FINALROM -DNDEBUG -o $out $in && {CROSS_STRIP} $out -N dummy-symbol-name"

def clean():
    if os.path.exists(".splache"):
        os.remove(".splache")
    shutil.rmtree("asm", ignore_errors=True)
    shutil.rmtree("assets", ignore_errors=True)
    shutil.rmtree("build", ignore_errors=True)

def create_build_script(linker_entries: List[LinkerEntry]):
    built_objects: Set[Path] = set()

    def build(
        object_paths: Union[Path, List[Path]],
        src_paths: List[Path],
        task: str,
        variables: Dict[str, str] = {},
        implicit_outputs: List[str] = [],
    ):
        if not isinstance(object_paths, list):
            object_paths = [object_paths]

        object_strs = [str(obj) for obj in object_paths]

        for object_path in object_paths:
            if object_path.suffix == ".o":
                built_objects.add(object_path)
            ninja.build(
                outputs=object_strs,
                rule=task,
                inputs=[str(s) for s in src_paths],
                variables=variables,
                implicit_outputs=implicit_outputs,
            )

    ninja = ninja_syntax.Writer(open(str(ROOT / "build.ninja"), "w"), width=9999)

    ninja.rule(
        "as",
        description="as $in",
        command=f"cpp {COMMON_INCLUDES} $in -o - | {CROSS_AS} -G0 {COMMON_INCLUDES} -EB -mtune=vr4300 -march=vr4300 -o $out",
    )

    ninja.rule(
        "as_libultra",
        description="as $in",
        command=f"COMPILER_PATH={CC_DIR} {AS} -c -G 0 -D_LANGUAGE_ASSEMBLY -DBUILD_VERSION=VERSION_K -D_FINALROM -D_MIPS_SIM=1 -P -mips2 {COMMON_INCLUDES} -o $out $in && {CROSS_STRIP} $out -N dummy-symbol-name",
    )

    ninja.rule(
        "bin",
        description="bin $in",
        command=f"{CROSS_LD} -r -b binary $in -o $out",
    )

    ninja.rule(
        "cc",
        description="cc $in",
        command=f"COMPILER_PATH={CC_DIR} {GAME_CC_CMD}",
    )

    ninja.rule(
        "ld",
        description="link $out",
        command=f"{CROSS_LD} -T undefined_syms.txt -T undefined_syms_auto.txt -T undefined_funcs_auto.txt -Map $mapfile -T $in -o $out",
    )

    ninja.rule(
        "sha1sum",
        description="sha1sum $in",
        command="sha1sum -c $in && touch $out",
    )
    
    ninja.rule(
        "z64",
        description="rom $out",
        command=f"{CROSS_OBJCOPY} $in $out -O binary",
    )

    for entry in linker_entries:
        seg = entry.segment

        if seg.type[0] == ".":
            continue

        if entry.object_path is None:
            continue

        if isinstance(seg, splat.segtypes.n64.header.N64SegHeader):
            build(entry.object_path, entry.src_paths, "as")
        elif isinstance(seg, splat.segtypes.common.asm.CommonSegAsm) or isinstance(
            seg, splat.segtypes.common.data.CommonSegData
        ):
            if "ultralib" in str(entry.src_paths[0]):
                build(entry.object_path, entry.src_paths, "as_libultra")
            else:
                build(entry.object_path, entry.src_paths, "as")
        elif isinstance(seg, splat.segtypes.common.c.CommonSegC):
            build(entry.object_path, entry.src_paths, "cc", variables={"flags": "-O2"})
        elif isinstance(seg, splat.segtypes.common.bin.CommonSegBin):
            build(entry.object_path, entry.src_paths, "bin")
        else:
            print(f"ERROR: Unsupported build segment type {seg.type}")
            sys.exit(1)

    ninja.build(
        ELF_PATH,
        "ld",
        LD_PATH,
        implicit=[str(obj) for obj in built_objects],
        variables={"mapfile": MAP_PATH},
    )

    ninja.build(
        Z64_PATH,
        "z64",
        ELF_PATH,
    )

    ninja.build(
        OK_PATH,
        "sha1sum",
        "checksum.sha1",
        implicit=[Z64_PATH],
    )

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Configure the project")
    parser.add_argument(
        "-c",
        "--clean",
        help="Clean extraction and build artifacts",
        action="store_true",
    )
    args = parser.parse_args()

    if args.clean:
        clean()

    subprocess.run(["tools/compression.py", "d", str(ROOT / "baserom.z64"), str(ROOT / "build/baserom_dec.z64")])

    split.main([YAML_FILE], modes="all", verbose=False)

    linker_entries = split.linker_writer.entries
    create_build_script(linker_entries)