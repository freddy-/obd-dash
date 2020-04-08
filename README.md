# OBD Dash display

Auxiliar display that shows some information from my car ECU through OBD ISO 9141-2 bus.

This project is based in a chinese ELM327 OBD to Bluetooth, the module was disassembled and the pcb traces between the ELM and bluetooth was cut and rewired to Arduino wich is responsible for ELM initialization and query for the ECU data.

The current ECU data displayed are:
* Battery voltage
* RPM
* MAP
* Spark advace
* Intake temperature
* Cooland temperature
* TPS

[![Obd Display](https://img.youtube.com/vi/8ltNNvUFt8k/0.jpg)](https://www.youtube.com/watch?v=8ltNNvUFt8k)

Schematic
<img src="hw/obd-dash/obd-dash.svg">

Pictures
<table>
  <tr>
    <td><img alt="VW logo splash screen" src="hw/images/IMG_20191207_112708.jpg"></td>
    <td><img src="hw/images/IMG_20191213_225649.jpg"></td>
  </tr>
</table>


