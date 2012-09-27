#!/usr/bin/env python
import sys, os

def options(opt):
    pass

def configure(cfg):
    cfg.env.CXXFLAGS_BENCH = ['-std=c++0x',]

def build(bld):
    bld(
        target          = 'bench',
        export_includes = '.',
        use             = ['BENCH'],
    )
