#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""a number guessing game to convert from hex to decimal"""
from __future__ import print_function
import argparse
import random

FORMAT_BASES = {
    "hex": hex,
    "bin": bin,
    "dec": int
}

PARSE_BASES = {
    "hex": lambda x: int(str(x), 16),
    "bin": lambda x: int(str(x), 2),
    "dec": int
}

def parse_args():
    """parses arguments"""
    parser = argparse.ArgumentParser()
    parser.add_argument("--from_base", '-f', choices=PARSE_BASES.keys(), default='hex')
    parser.add_argument("--to_base", "-t", choices=FORMAT_BASES.keys(), default='dec')
    return parser.parse_args()

def game(from_base, to_base):
    """A game to convert between bases"""
    format_question = FORMAT_BASES[from_base]
    format_answer = FORMAT_BASES[to_base]
    parser = PARSE_BASES[to_base]
    while True:
        number = random.randint(0, 16)
        print(format_question(number))
        try:
            guess = parser(input())
            print(guess == number, format_answer(number))
        except ValueError:
            print("please put your answer in {format}".format(format=to_base))
        except EOFError:
            break
def main():
    """main method"""
    args = parse_args()
    game(args.from_base, args.to_base)

if __name__ == "__main__":
    main()
