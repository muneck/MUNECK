import random

f = "flick"
h = "hold"
a = "avoid"
bpm = 140
step_len = 15 / bpm

fast = 8
mid = 24
slow = 32
note_num = 0

def convert_steps(steps):
	return 15 / bpm * steps

def convert(steps):
	a, b = map(int, steps.split(":"))
	return convert_steps((a - 1) * 16 + b - 1)

def rdt():
	return random.randint(-2, 2)

def add(typ, rail, start_step: str, end_step: str, delay_steps):
	print("\t\t{")
	print("\t\t\t\"Type\": \"%s\"," % typ)
	print("\t\t\t\"Rail\": %d," % rail)
	print("\t\t\t\"Length\": %f," % (convert(end_step) - convert(start_step)))
	print("\t\t\t\"StartTime\": %f," % convert(start_step))
	print("\t\t\t\"DelayTime\": %f" % convert_steps(delay_steps))
	print("\t\t},")
	global note_num
	note_num += 1

def add_str(typ, rail, start_step, end_step, delay_steps):
	print("\t\t{")
	print("\t\t\t\"Type\": \"%s\"," % typ)
	print("\t\t\t\"Rail\": %d," % rail)
	print("\t\t\t\"Length\": %f," % (end_step - start_step))
	print("\t\t\t\"StartTime\": %f," % start_step)
	print("\t\t\t\"DelayTime\": %f" % convert_steps(delay_steps))
	print("\t\t},")
	global note_num
	note_num += 1


print("{")
print("\t\"NoteNum\": ,")
print("\t\"NoteList\": [")

start = convert("3:01")
end = convert("116:01")

while (start < end):
	if (random.random() < 1):
		add_str(f, rdt(), start, start, random.choice([fast, mid, mid, slow, slow]))
	start += convert_steps(4)

print("\t]")
print("}")
print(note_num)