import subprocess
import os

gcc = "arm-none-eabi-gcc"
gccp = "arm-none-eabi-g++"
MACH="cortex-m3"
CFLAGS=  f"-c -mcpu={MACH} -mthumb -std=gnu11 -O0"
CFLAGSP=  f"-c -mcpu={MACH} -mthumb -std=c++11 -O0"
ldfile = ""
subprocess.run("rm -f build/obj/*")
subprocess.run("rm -f build/output/*")

# buid driver
link1= "stm32f103c8t6"
for data1 in os.listdir(link1):
    # xuli Driver
    if(data1 == "driver"):
        link2 = f"{link1}/{data1}"
        for data2 in os.listdir(link2):
            link3 = f"{link2}/{data2}"
            for data3 in os.listdir(link3):
                if(data3.split(".")[-1]=="c"):
                    file = f"{link3}/{data3}"
                    line = f"{gcc} {CFLAGS} -o build/obj/{data3.split(".")[0]}.o {file}"
                    print(line)
                    subprocess.run(line)


    # xuli Startup
    if(data1 == "startup"):
        link2 = f"{link1}/{data1}"
        for data2 in os.listdir(link2):
                file = f"{link2}/{data2}"
                line = f"{gcc} {CFLAGS} -o build/obj/{data2.split(".")[0]}.o {file}"
                print(line)
                subprocess.run(line)

    if(data1 == "linker"):
        link2 = f"{link1}/{data1}"
        for data2 in os.listdir(link2):
            ldfile = f"{link2}/{data2}"
        
                    
#build layerUnit
link1 = "layer_unit"    
for data1 in os.listdir(link1):
    link2 = f"{link1}/{data1}"
    for data2 in os.listdir(link2):
        if(data2.split(".")[-1]=="c"):
            file = f"{link2}/{data2}"
            line = f"{gcc} {CFLAGS} -o build/obj/{data2.split(".")[0]}.o {file}"
            print(line)
            subprocess.run(line)


#build layerUnit
link1 = "layer_integration"    
for data1 in os.listdir(link1):
    link2 = f"{link1}/{data1}"
    for data2 in os.listdir(link2):
        if(data2.split(".")[-1]=="c"):
            file = f"{link2}/{data2}"
            line = f"{gcc} {CFLAGS} -o build/obj/{data2.split(".")[0]}.o {file}"
            print(line)
            subprocess.run(line)



# build main
link1 = "src"    
for data1 in os.listdir(link1):
    if(data1.split(".")[0]=="main"):
        file = f"{link1}/{data1}"
        line = f"{gcc} {CFLAGS} -Ilayer_integration -o build/obj/{data1.split(".")[0]}.o {file}"
        print(line)
        subprocess.run(line)

# subprocess.run("arm-none-eabi-gcc --version")
dir = "build/obj"
files = []
for data in os.listdir(dir):
    if data.endswith('.o'):  # Chỉ lấy các file có đuôi là .o
        files.append(f"{dir}/{data}")

file_list = " ".join(files)
line = f"arm-none-eabi-gcc -nostdlib -T {ldfile} -o build/output/program.elf {file_list}"
print(line)
subprocess.run(str(line))

# subprocess.run("arm-none-eabi-gcc --version")
line = "arm-none-eabi-objcopy -O ihex build/output/program.elf build/output/program.hex"
print(line)
subprocess.run(str(line))

# subprocess.run("arm-none-eabi-gcc --version")
line = "arm-none-eabi-objcopy -O binary build/output/program.elf build/output/program.bin"
print(line)
subprocess.run(str(line))

subprocess.run("arm-none-eabi-size build/output/program.elf")