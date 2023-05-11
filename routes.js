import { Router } from "express";
import { SerialPort, ReadlineParser } from 'serialport';
const path = '/dev/ttyACM0'
const baudRate = 9600
const port = new SerialPort({ path, baudRate })

const router = Router();

router.post('/prender', (req, res) => {
    port.write('B');
    res.send("OK");
    console.log("mandar b");
})

export default router;