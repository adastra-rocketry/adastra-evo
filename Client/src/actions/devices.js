import {GET_DEVICE_SUCCESS, BACK_TO_DEVICE_SELECTION} from '../actionConstants/devices';

export function getDeviceSuccess(device) {
    return {
        type: GET_DEVICE_SUCCESS,
        device
    }
}

export function backToDeviceSelection(device) {
    return {
        type: BACK_TO_DEVICE_SELECTION,
        device
    }
}

export function getDevice() {
    return async dispatch => {
        const device = await navigator.bluetooth.requestDevice({
            // filters: [...] <- Prefer filters to save energy & show relevant devices.
               acceptAllDevices: true
            });
        dispatch(getDeviceSuccess(device));
    };
  }