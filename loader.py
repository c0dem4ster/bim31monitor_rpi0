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

url = 'http://wienerlinien.at/ogd_realtime/monitor?rbl=2167&sender=T3bvytrlebIJABzK'

bin = '/home/pi/bim31monitor_rpi0/a.out'

# utility for running other programs
def run(args):
  proc = Popen(args, stdout = PIPE)
  proc.communicate()
  proc.wait()

# main part
def main():
  try:
    # download & parse json file
    raw = request.urlopen(url)
    data = json.loads(raw.read().decode("utf-8"))['data']['monitors'][0]['lines'][0]
  except:
    # fill data with dummy content
    data = {
      'barrierFree': False,
      'departures': {
        'departure': [{'departureTime': {'countdown': 0}} for i in range(3)]
      }
    }
    print('couldn\'t download {}.'.format(url))
    print('are you connected to the internet?')


  # write content to data file
  with open('data', 'w') as f:
    line_barrierfree = data['barrierFree']

    for i in range(3):
      f.write(str(data['departures']['departure'][i]['departureTime']['countdown']) + '\n')
      f.write(str(data['departures']['departure'][i]['vehicle']['barrierFree']
        if 'vehicle' in data['departures']['departure'][i]
        else line_barrierfree) + '\n')
  
  # print tram positions to screen
  try:
    run([bin])
  except:
    print('couldn\'t find {}.'.format(bin))
    print('have you compiled the binaries with \'make\'?')


if __name__ == '__main__':
  while True:
    main()
    sleep(6)

