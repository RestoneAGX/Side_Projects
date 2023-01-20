1. we take each character
2. check if the character == '#', if so we start skipping
3. if the character == '\n', then we stop skipping, load the input into our ouput buffer (if necessary),  start set out idx == 0, and skip 3 characters (or just skip until its not a word through a check)
4. check if it's a word [For words like usemtl, we could compress using a huffman code or by compressing the .mtl filenames and making a config file that would store their definitions]
	1. If it is word, skip or compress if able
5. if !word, then load until a ' ' is reached (while skipping, check for a dot)
6. convert the data between the 2 spaces to a float32 or int16 (depending on the check)
7. Overwrite previous writes it


If the word is:
v -> load as normal
f -> create a int reference point and the corresponding values will be the numerical offsets from that point (they can be + or -)
s -> normal int8 or 16 conversion

#TODO:[Look more into the keywords and the expected value, use that to find shorter representations]
