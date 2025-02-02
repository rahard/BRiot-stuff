# Script to capture (scrap) data from OpenMPPT web server (ESP32 based)
# and save some of the data into a file.
# Configuration is still scattered
# Should have configuration at the begining of the script.
# 2024-2025, Creative Common, Budi Rahardjo
#

### Configuration

# file to write - you should add this line at the begining of the file
# time,solarv,mppv,bateryv,baterytemp,charge
CSVfile="openMPP.csv"
openmpptURL="http://192.168.4.133"

### No need to touch anything below this 

import requests
r = requests.get(openmpptURL)
#print(r.text)

from bs4 import BeautifulSoup

# Parse the HTML
soup = BeautifulSoup(r.text, 'html.parser')

# Extract and print the plain text
plain_text = soup.get_text(separator="\n").strip()
print(plain_text)

lines = plain_text.splitlines()

def extract_localtime(linevar):
    local_time = linevar.split(": ", 1)[1].split(" DST")[0]
    #print(f"Local Time: {local_time}")
    return(local_time)

def extract_solar_voltage(linevar):
    solar_voltage = linevar.split(": ", 1)[1].split(" Volt")[0]
    return(solar_voltage)

def extract_mpp_voltage(linevar):
    mpp_voltage = linevar.split(": ", 1)[1].split(" Volt")[0]
    return(mpp_voltage)

def extract_charge(linevar):
    charge = linevar.split(": ", 1)[1].split("%")[0]
    return(charge)

def extract_batv(linevar):
    batv = linevar.split(": ", 1)[1].split(" Volt")[0]
    return(batv)

def extract_batt(linevar):
    batt = linevar.split(": ", 1)[1].split("°C")[0]
    return(batt)

print("Hasil =====>")
for line in lines:
    if line.startswith("Local time:"):
        waktu = extract_localtime(line)
        print("Waktu:", waktu)
    if line.startswith("Solar panel open circuit voltage:"):
        solarv = extract_solar_voltage(line)
        print("Solar voltage:", solarv)
    if line.startswith("MPP"):
        mppv = extract_mpp_voltage(line)
        print("MPP voltage:", mppv)
    if line.startswith("Battery voltage:"):
        batv = extract_batv(line)
        print("Battery voltage:", batv)
    if line.startswith("Charge state:"):
        charge = extract_charge(line)
        print("Charge state:", charge)
    if line.startswith("Battery temperature:"):
        batt = extract_batt(line)
        print("Battery temperature:", batt)


# combine everything into one line
# local time, solar volt, MPP volt, batre volt, batre temp, persen charge
combine = waktu +',' + solarv +',' + mppv +',' + batv +',' + batt +',' + charge + "\n"

# save into CSV
f = open(CSVfile, "a")
f.write(combine)
f.close()
