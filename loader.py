#
#  @author: Theodor Fragner (theodor[at]fragner.org)
#  @date  : May, 24. 2019
#  @descr : program downloads a json file from a
#           web server, parses it into a text
#           file and periodically prints it to the
#           display
#

import json
from time import sleep
from urllib import request
from subprocess import Popen, PIPE

# utility for running other programs
def run(args):
  proc = Popen(args, stdout = PIPE)
  proc.communicate()
  proc.wait()

# main part
def main():
  # download & parse json file
  raw = request.urlopen('http://wienerlinien.at/ogd_realtime/monitor?rbl=2167&sender=k34RXngkrRDzfT2x')
  data = json.loads(raw.read().decode("utf-8"))

  # write content to data file
  with open('data', 'w') as f:
    line_barrierfree = data['data']['monitors'][0]['lines'][0]['barrierFree']

    for i in range(3):
      f.write(str(data['data']['monitors'][0]['lines'][0]['departures']['departure'][i]['departureTime']['countdown']) + '\n')
      f.write(str(data['data']['monitors'][0]['lines'][0]['departures']['departure'][i]['vehicle']['barrierFree']
        if 'vehicle' in data['data']['monitors'][0]['lines'][0]['departures']['departure'][i]
        else line_barrierfree) + '\n')
  
  # print tram positions to screen
  run(['/home/pi/bim_monitor/a.out'])

if __name__ == '__main__':
  while True:
    main()
    sleep(0.5)