# this function will receive a txt file and extract all words of 3 letters.
# group the words that are formed by the same letters
# filter to remain only the groups that have more than 2 words
# and save the result in a txt file
# and sort the groups by the number of words in the group
# and eliminate duplicates


import re
import os

def build_dictionary(file_path):
    # read
    with open(file_path, 'r') as file:
        words = file.read().split('\n')
    # filter
    words = [word for word in words if re.match(r'^[a-z]{3}$', word)]
    # group
    groups = {}
    for word in words:
        key = ''.join(sorted(word))
        if key not in groups:
            groups[key] = []
        groups[key].append(word)
    # filter
    groups = {key: value for key, value in groups.items() if len(value) > 2}
    # sort
    groups = dict(sorted(groups.items(), key=lambda item: len(item[1]), reverse=True))
    # write
    with open('dictionary.txt', 'w') as file:
        for key, value in groups.items():
            file.write(f'{key}: {value}\n')

if __name__ == '__main__':
    build_dictionary('words.txt')
