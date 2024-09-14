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

#readConfigure_Json
CONFIG_FILE_PATH = os.path.join(FILEDIR, "configure.json")
with open(CONFIG_FILE_PATH, 'r') as file:
    DATA = json.load(file)

#configure Infomation    
CPL      = DATA["compiler"]
CPU_AR   = DATA["cpu_architecture"]
FLAG_CPL = f"-c -mcpu={CPU_AR} -mthumb -std=gnu11 -O5"
LINKER   = f"hardware/{DATA["hardware"]}/{DATA["linkerfile"]}"
STARTUP  = f"hardware/{DATA["hardware"]}/{DATA["startupfile"]}"

#_____________EXECUTION________________________
list_data = []
list_header = []
index = 0

def execution_file(link):
    with open(link,"r", encoding='utf-8') as file:
        for data in file:
            if("#include" in data):
                if("\"") in data:
                    data = data.split("#include")[1]
                    data = data.strip()
                    data = data.replace("\"","")
                    data = data.replace("../","")
                    data = data.replace("/","\\")
                    link = os.path.join(DIR_SRC,data)
                    list_data.append(link)

def generate_C(data):
    link_input = str(data).replace(".h",".c")
    link_output = os.path.join(DIR_OBJ,f"{str(data).split("\\")[-1].split(".")[0]}.o")
    line = f"{CPL} {FLAG_CPL} {link_input} -o {link_output}"
    run_command(line)
    print(f"generating : {link_output}")


def generate_S(data):
    link_input = data
    link_output = os.path.join(DIR_OBJ,f"{str(data).split("\\")[-1].split(".")[0]}.o")
    line = f"{CPL} -c {link_input} -o {link_output}"
    run_command(line)
    print(f"generating : {link_output}")

delete_files()

list_data.append(os.path.join(DIR_SRC,str(STARTUP).replace("/","\\")))
list_data.append(os.path.join(DIR_SRC,"main.c"))
sw = 0

while 1:
    lenght_data = len(list_data)
    if(index == lenght_data):
        sw = 1
        break
    try:
        execution_file(list_data[index])
        print(f"pass {index+1} : {list_data[index]}")
    except:
        print(f"error {index+1} : {list_data[index]}\n")
        break
    index = index + 1

if(sw == 1):
    print("complete generate\n")
    unique_file_list = list(set(list_data))
    unique_file_list.sort()
    for data in unique_file_list:
        if("general" not in data):
            if(".h" in data or ".c" in data):
                generate_C(data)
            elif(".s" in data):
                generate_S(data)

    print("\nFinish output:")
    dir = "build/obj"
    files = []
    for data in os.listdir(dir):
        files.append(f"{dir}/{data}")
        
    run_command(f"arm-none-eabi-gcc -nostdlib -T {LINKER} -g -o build/output/program.elf {" ".join(files)}")
    run_command("arm-none-eabi-size build/output/program.elf")

    if(DATA["hex_file"] == "on"): run_command("arm-none-eabi-objcopy -O ihex build/output/program.elf build/output/program.hex")
    if(DATA["bin_file"] == "on"): run_command("arm-none-eabi-objcopy -O binary build/output/program.elf build/output/program.bin")
    if(DATA["map_file"] == "on"): run_command("arm-none-eabi-objdump -x build/output/program.elf > build/output/program.map")
    if(DATA["asm_file"] == "on"): run_command("arm-none-eabi-objdump -d build/output/program.elf > build/output/program.asm")