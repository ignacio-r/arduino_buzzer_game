

const { SerialPort, ReadlineParser } = require('serialport')
const path = '/dev/ttyACM0'
const baudRate = 9600
const port = new SerialPort({ path, baudRate })
const parser = new ReadlineParser()
port.pipe(parser)
parser.on('data', console.log)
//port.write('ROBOT PLEASE RESPOND\n')
// ROBOT ONLINE

// Creating the parser and piping can be shortened to
// const parser = port.pipe(new ReadlineParser())

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
  });

  
  readline.question('prender 1, apagar 0\n', num => {
    while(true){
        if(num == 0){
            port.write('0')
            readline.close()
        }else if(num == 1){
            port.write('1')
            readline.close()
        }
    }
  });

