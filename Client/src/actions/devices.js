import {
  GET_DEVICE_SUCCESS,
  BACK_TO_DEVICE_SELECTION,
  DEVICE_CHARACTERISTIC_CHANGE_RECEIVED,
} from "../actionConstants/devices";
import { history } from "../routers/AppRouter";
import { parseDataPoint } from "../util/datapointParser";

export function getDeviceSuccess(
  device,
  server,
  service,
  currentDeviceStateCharacteristic
) {
  return {
    type: GET_DEVICE_SUCCESS,
    device,
    server,
    service,
    currentDeviceStateCharacteristic,
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
    const currentDeviceStateCharacteristic = await service.getCharacteristic(
      0x2ac2
    );
    dispatch(
      getDeviceSuccess(
        device,
        server,
        service,
        currentDeviceStateCharacteristic
      )
    );
  };
}

export function characteristicChangeReceived(data) {
  return {
    type: DEVICE_CHARACTERISTIC_CHANGE_RECEIVED,
    data,
  };
}

function characteristicvaluechangedHandler(dispatch, event) {
  const dataPoint = parseDataPoint(event.target.value);
  dispatch(characteristicChangeReceived(dataPoint));
}

function gattserverdisconnectedHandler(dispatch) {
  dispatch(backToDeviceSelection());
}

export function enableLiveDataSubscription() {
  return async (dispatch, getState) => {
    const currentDeviceStateCharacteristic = getState().device.currentDeviceStateCharacteristic;

    await currentDeviceStateCharacteristic.startNotifications();
    currentDeviceStateCharacteristic.addEventListener(
      "characteristicvaluechanged",
      characteristicvaluechangedHandler.bind(this, dispatch)
    );
    currentDeviceStateCharacteristic.addEventListener(
      "gattserverdisconnected",
      gattserverdisconnectedHandler.bind(this, dispatch)
    );
  };
}

export function disableLiveDataSubscription() {
  return async (dispatch, getState) => {
    const currentDeviceStateCharacteristic = getState().device.currentDeviceStateCharacteristic;
    currentDeviceStateCharacteristic.stopNotifications();
    currentDeviceStateCharacteristic.removeEventListener(
      "characteristicvaluechanged",
      characteristicvaluechangedHandler.bind(this, dispatch)
    );
  };
}
