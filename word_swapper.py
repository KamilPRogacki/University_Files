import random
def swap_words(input_string):
    words = input_string.split()
    replacements = ["funny", "pineapple", "chocolate", "very"]
    words_to_swap = ["apple", "tasty"]
    
    for i in range(len(words)):
        if words[i] in words_to_swap:
            words[i] = replacements[random.randint(0, 1)]
    
    result = ' '.join(words)


    return result

input_text = "apple is tasty"
output = swap_words(input_text)
print(output)