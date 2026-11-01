#!/usr/bin/env python3
"""Visualizzatore per l'oscilloscopio RP2040 + ADS7883.
Uso: python viewer.py COM5 --rate 1000000 --trig 0 --edge rise --mode auto
"""
import argparse, struct
import numpy as np
import serial
import matplotlib.pyplot as plt

VREF, OFFSET, PROBE = 5.0, 2.5, 10.0   # 5 V riferimento, offset 2,5 V, sonda x10

p = argparse.ArgumentParser()
p.add_argument("port")
p.add_argument("--rate", type=int, default=1_000_000)
p.add_argument("--trig", type=float, default=0.0, help="livello trigger in volt alla punta")
p.add_argument("--edge", choices=["rise", "fall"], default="rise")
p.add_argument("--mode", choices=["free", "auto", "normal"], default="auto")
p.add_argument("--probe", type=float, default=PROBE)
a = p.parse_args()

ser = serial.Serial(a.port, 115200, timeout=0.5)
level = int(np.clip((a.trig / a.probe + OFFSET) / VREF * 4096, 0, 4095))
mode = {"free": 0, "auto": 1, "normal": 2}[a.mode]
ser.write(f"SET {a.rate} {level} {1 if a.edge == 'rise' else 0} {mode}\n".encode())

def read_frame():
    while True:
        b = ser.read(1)
        if not b:
            return None
        if b == b"\xa5" and ser.read(1) == b"\x5a":
            break
    h = ser.read(8)
    if len(h) < 8:
        return None
    rate, n, trig = struct.unpack("<IHB", h[:7])
    raw = ser.read(2 * n)
    if len(raw) < 2 * n:
        return None
    return rate, bool(trig), np.frombuffer(raw, dtype="<u2")

plt.ion()
fig, ax = plt.subplots()
(line,) = ax.plot([], [])
ax.set_xlabel("tempo [ms]"); ax.set_ylabel("tensione [V]"); ax.grid(True)
while plt.fignum_exists(fig.number):
    f = read_frame()
    if f is None:
        plt.pause(0.01); continue
    rate, trig, codes = f
    volts = (codes * VREF / 4096 - OFFSET) * a.probe
    t_ms = np.arange(len(codes)) / rate * 1000
    line.set_data(t_ms, volts)
    ax.set_xlim(0, t_ms[-1])
    span = max(float(np.ptp(volts)), 0.5)
    mid = float(volts.mean())
    ax.set_ylim(mid - span, mid + span)
    ax.set_title(f"{rate/1000:.0f} kSPS  {'TRIG' if trig else 'AUTO'}  "
                 f"Vpp={np.ptp(volts):.2f} V")
    plt.pause(0.001)
