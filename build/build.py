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
CONFIG_FILE_PATH = "build/configure.json"
with open(CONFIG_FILE_PATH, 'r') as file:
    DATA = json.load(file)

CPU_AR   = DATA["cpu_architecture"]

CP_C     = DATA["compiler_c"]
CP_CPL   = DATA["compiler_c++"]
CP_ASM   = DATA["compiler_asm"]
OTP      = DATA["optimazation"]

FLAG_C   = f"-mcpu={CPU_AR} -mthumb -c {OTP} "
FLAG_CPL = f"-mcpu={CPU_AR} -mthumb -c {OTP} "
FLAG_ASM = f"-mcpu={CPU_AR} -mthumb"

LINKER   = f"hardware/{DATA["hardware"]}/{DATA["linkerfile"]}"
STARTUP  = f"hardware/{DATA["hardware"]}/{DATA["startupfile"]}"
MAIN     = DATA["main"] 


list_data = []
index = 0
#_____________EXECUTION________________________
def generate_C(data):
    link_input = str(data).replace(".h",".c")
    link_output = os.path.join(DIR_OBJ,f"{str(data).split("\\")[-1].split(".")[0]}.o")
    line = f"{CP_C} {FLAG_C} {link_input} -o {link_output}"
    run_command(line)
    print(f"generating : {link_output}")

def generate_CPL(data):
    link_input = str(data).replace(".h",".cpp")
    link_output = os.path.join(DIR_OBJ,f"{str(data).split("\\")[-1].split(".")[0]}.o")
    line = f"{CP_CPL} {FLAG_CPL} {link_input} -o {link_output}"
    run_command(line)
    print(f"generating : {link_output}")

def generate_S(data):
    link_input = data
    link_output = os.path.join(DIR_OBJ,f"{str(data).split("\\")[-1].split(".")[0]}.o")
    line = f"{CP_ASM} {FLAG_ASM} {link_input} -o {link_output}"
    print(line)
    run_command(line)
    print(f"generating : {link_output}")

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

# START
delete_files()
list_data.append(os.path.join(DIR_SRC,str(STARTUP).replace("/","\\")))
list_data.append(os.path.join(DIR_SRC,str(MAIN).replace("/","\\")))

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
unique_file_list = list(set(list_data))
unique_file_list.sort()
print("complete generate\n")

if(sw == 1):
    for data in unique_file_list:
        if("general" not in data):
            if((".h" in data)):
                if("hardware" in data):
                    generate_C(data)
                else:
                    generate_C(data)
            elif(".c" in data):
                generate_C(data)
            elif(".cpp" in data):
                generate_CPL(data)
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