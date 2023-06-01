import { Router } from "express";
import { SerialPort, ReadlineParser } from 'serialport';
import five from "johnny-five";
// const path = '/dev/ttyACM0'
// const baudRate = 9600
// const port = new SerialPort({ path, baudRate })

const router = Router();

const board = new five.Board();

router.post('/prender', (req, res) => {
    board.on("ready", () => {
        const blueLed = new five.Led(7);
        const redLed = new five.Led(8);

        blueLed.on();
        redLed.on();
    })

    res.send("OK");
})

export default router;