#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'build/baserom_dec.z64'
    config['myimg'] = 'build/mariotennis.z64'
    config['mapfile'] = 'build/mariotennis.map'
    config['source_directories'] = ['.']
    config["make_command"] = ["ninja"]
    config["objdump_flags"] = ["-M", "reg-names=32"]
    config["expected_dir"] = f"expected/"
