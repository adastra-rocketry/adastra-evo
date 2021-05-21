import {
  GET_DEVICE_SUCCESS,
  BACK_TO_DEVICE_SELECTION,
  DEVICE_CHARACTERISTIC_CHANGE_RECEIVED,
} from "../constants/devices";
import { history } from "../routers/AppRouter";
import { parseDataPoint } from "../util/datapointParser";

export function getDeviceSuccess(
  device,
  server,
  service,
  currentDeviceState_MainData_Characteristic,
  currentDeviceState_AccData_Characteristic,
  currentDeviceState_GData_Characteristic,
  currentDeviceState_MagData_Characteristic,
  currentDeviceState_IMUData_Characteristic,
  currentDeviceState_PressureData_Characteristic,
  currentDeviceState_KalmanData_Characteristic
) {
  return {
    type: GET_DEVICE_SUCCESS,
    device,
    server,
    service,
    currentDeviceState_MainData_Characteristic,
    currentDeviceState_AccData_Characteristic,
    currentDeviceState_GData_Characteristic,
    currentDeviceState_MagData_Characteristic,
    currentDeviceState_IMUData_Characteristic,
    currentDeviceState_PressureData_Characteristic,
    currentDeviceState_KalmanData_Characteristic
  };
}

export function backToDeviceSelection() {
  return async (dispatch, getState) => {
    const device = getState().device.selected;

    dispatch(disableLiveDataSubscription());

    if (device.gatt.connected) {
      device.gatt.disconnect();
    }
    return {
      type: BACK_TO_DEVICE_SELECTION,
    };
  };
}

export function getDevice() {
  return async (dispatch) => {
    const device = await navigator.bluetooth.requestDevice({
      filters: [{ name: "AdAstra Evo" }],
      optionalServices: ["0000181c-0000-1000-8000-00805f9b34fb"],
    });
    const server = await device.gatt.connect();
    const service = await server.getPrimaryService(
      "0000181c-0000-1000-8000-00805f9b34fb"
    );
    const currentDeviceState_MainData_Characteristic = await service.getCharacteristic(
      0x2ac0
    );
    const currentDeviceState_AccData_Characteristic = await service.getCharacteristic(
      0x2ac1
    );
    const currentDeviceState_GData_Characteristic = await service.getCharacteristic(
      0x2ac2
    );
    const currentDeviceState_MagData_Characteristic = await service.getCharacteristic(
      0x2ac3
    );
    const currentDeviceState_IMUData_Characteristic = await service.getCharacteristic(
      0x2ac4
    );
    const currentDeviceState_PressureData_Characteristic = await service.getCharacteristic(
      0x2ac5
    );
    const currentDeviceState_KalmanData_Characteristic = await service.getCharacteristic(
      0x2ac6
    );
    dispatch(
      getDeviceSuccess(
        device,
        server,
        service,
        currentDeviceState_MainData_Characteristic,
        currentDeviceState_AccData_Characteristic,
        currentDeviceState_GData_Characteristic,
        currentDeviceState_MagData_Characteristic,
        currentDeviceState_IMUData_Characteristic,
        currentDeviceState_PressureData_Characteristic,
        currentDeviceState_KalmanData_Characteristic
      )
    );
  };
}

export function characteristicChangeReceived(data, name) {
  return {
    type: DEVICE_CHARACTERISTIC_CHANGE_RECEIVED,
    data,
    name
  };
}

function characteristicvaluechangedHandler(dispatch, name, event) {
  const dataPoint = parseDataPoint(event.target.value, name);
  dispatch(characteristicChangeReceived(dataPoint, name));
}

function gattserverdisconnectedHandler(dispatch) {
  dispatch(backToDeviceSelection());
}

export function enableLiveDataSubscription() {
  return async (dispatch, getState) => {

    let register = async (name) => {
      let characteristic = getState().device.currentDeviceStateCharacteristics[name];
      await characteristic.startNotifications();
      characteristic.addEventListener(
        "characteristicvaluechanged",
        characteristicvaluechangedHandler.bind(this, dispatch, name)
      );
      characteristic.addEventListener(
        "gattserverdisconnected",
        gattserverdisconnectedHandler.bind(this, dispatch)
      );
    };

    await register("currentDeviceState_MainData_Characteristic");
    await register("currentDeviceState_AccData_Characteristic");
    await register("currentDeviceState_GData_Characteristic");
    await register("currentDeviceState_MagData_Characteristic");
    await register("currentDeviceState_IMUData_Characteristic");
    await register("currentDeviceState_PressureData_Characteristic");
    await register("currentDeviceState_KalmanData_Characteristic");

  };
}

export function disableLiveDataSubscription() {
  return async (dispatch, getState) => {
    const unregister = (name) => {
      let characteristic = getState().device.currentDeviceStateCharacteristics[name];
      characteristic.stopNotifications();
      characteristic.removeEventListener(
        "characteristicvaluechanged",
        characteristicvaluechangedHandler.bind(this, dispatch, name)
      );
    };

    await unregister("currentDeviceState_MainData_Characteristic");
    await unregister("currentDeviceState_AccData_Characteristic");
    await unregister("currentDeviceState_GData_Characteristic");
    await unregister("currentDeviceState_MagData_Characteristic");
    await unregister("currentDeviceState_IMUData_Characteristic");
    await unregister("currentDeviceState_PressureData_Characteristic");
    await unregister("currentDeviceState_KalmanData_Characteristic");
  };
}
