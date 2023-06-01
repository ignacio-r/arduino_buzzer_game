import { Router } from "express";
import { SerialPort, ReadlineParser } from 'serialport';
import five from "johnny-five";
const path = '/dev/ttyACM0'
const baudRate = 9600
const port = new SerialPort({ path, baudRate })

const router = Router();

const board = new five.Board();

router.post('/prender', (req, res) => {
    board.on("ready", () => {
        const blueLed = new Led(7);
        const redLed = new Led(8);
        // Blink every half second
        blueLed.on();
        redLed.on();
    });
    res.send("OK");
})

export default router;