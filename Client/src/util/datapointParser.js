let offset = 0;

function readNextValue(value, type) {
  let result = null;
  switch (type) {
    case "Uint16":
      result = value.getUint16(offset, true);
      break;
    case "Uint32":
      result = value.getUint32(offset, true);
      break;
    case "Float32":
      result = value.getFloat32(offset, true);
      break;
    default:
      throw new Error("Unknown Datatype");
  }

  offset = offset + 4;
  return result;
}

export function parseDataPoint(value) {
  offset = 0;
  let result = {
    state: readNextValue(value, "Uint16"),
    timestamp: readNextValue(value, "Uint32"),
    pressure: readNextValue(value, "Float32"),
    temperature: readNextValue(value, "Float32"),
    accX: readNextValue(value, "Float32"),
    accY: readNextValue(value, "Float32"),
    accZ: readNextValue(value, "Float32"),

    gX: readNextValue(value, "Float32"),
    gY: readNextValue(value, "Float32"),
    gZ: readNextValue(value, "Float32"),

    magX: readNextValue(value, "Float32"),
    magY: readNextValue(value, "Float32"),
    magZ: readNextValue(value, "Float32"),

    pitch: readNextValue(value, "Float32"),
    roll: readNextValue(value, "Float32"),
    yaw: readNextValue(value, "Float32"),

    pressureDelta: readNextValue(value, "Float32"),
    kalmanPressureDelta: readNextValue(value, "Float32"),
    altitude: readNextValue(value, "Float32"),

    kalmanPressure: readNextValue(value, "Float32"),
    kalmanAltitude: readNextValue(value, "Float32"),
    kalmanTemperature: readNextValue(value, "Float32"),
  };

  return result;
}
