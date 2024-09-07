import subprocess
import os
import json
import sys

sys.path.append("./")

# default function
def run_command(data):
    data = str(data).strip().split()
    subprocess.run(data,shell=True)

def delete_files():
    if sys.platform == 'win32':
        run_command('del /Q build\\obj\\*')
        run_command('del /Q build\\output\\*')
    else:
        run_command('rm -f build/obj/*')
        run_command('rm -f build/output/*')

#defautl execution
FILEDIR = os.path.dirname(__file__)
DIR_SRC = os.path.dirname(FILEDIR)
DIR_OBJ  = os.path.join(DIR_SRC,"build","obj")

CONFIG_FILE_PATH = os.path.join(FILEDIR, "configure.json")
with open(CONFIG_FILE_PATH, 'r') as file:
    DATA = json.load(file)
#default macro
CPL      = DATA["compiler"]
CPU_AR   = DATA["cpu_ar"]
FLAG_CPL = f"-c -mcpu={CPU_AR} -mthumb -std=gnu11 -O5"
LINKER = ""
STARTUP = ""

#_____________EXECUTION________________________
list_data = []
list_header = []
index = 0

def execution_file(link):
    with open(link,"r") as file:
        for data in file:
            if("#include" in data):
                if("\"") in data:
                    data = data.split()[1]
                    data = data.replace("/","\\")
                    data = data.strip("\"")
                    link = os.path.join(DIR_SRC,data)
                    list_data.append(link)

src_link = "software/general/general.h"
obj_name = ""
with open(src_link,"r") as file:
    obj_name = file.readline().split()[1].split("/")[3]
if obj_name:
    LINKER = f"hardware/{obj_name}/linker_file.ld"
    STARTUP = f"hardware/{obj_name}/startup_file.c"

list_data.append(os.path.join(DIR_SRC,str(STARTUP).replace("/","\\")))
list_data.append(os.path.join(DIR_SRC,"main.c"))

delete_files()

def execution_file(link):
    with open(link,"r") as file:
        for data in file:
            if("#include" in data):
                if("\"") in data:
                    data = data.split()[1]
                    data = data.strip("\"")
                    data = data.replace("../","")
                    data = data.replace("/","\\")
                    link = os.path.join(DIR_SRC,data)
                    list_data.append(link)

while 1:
    lenght_data = len(list_data)
    if(index == lenght_data):
        break
    try:
        execution_file(list_data[index])
        index = index + 1
    except:
        None

unique_file_list = list(set(list_data))
unique_file_list.sort()


for data in unique_file_list:
    if("general" not in data):
        link_input = str(data).replace(".h",".c")
        link_output = os.path.join(DIR_OBJ,f"{str(data).split("\\")[-1].split(".")[0]}.o")
        line = f"{CPL} {FLAG_CPL} {link_input} -o {link_output}"
        run_command(line)


dir = "build/obj"
files = []
for data in os.listdir(dir):
    if data.endswith('.o'): 
        files.append(f"{dir}/{data}")

file_list = " ".join(files)
line = f"arm-none-eabi-gcc -nostdlib -T {LINKER} -o build/output/program.elf {file_list}"
subprocess.run(str(line))

line = "arm-none-eabi-objcopy -O ihex build/output/program.elf build/output/program.hex"
print(line)
subprocess.run(str(line))

line = "arm-none-eabi-objcopy -O binary build/output/program.elf build/output/program.bin"
print(line)
subprocess.run(str(line))

subprocess.run("arm-none-eabi-size build/output/program.elf")