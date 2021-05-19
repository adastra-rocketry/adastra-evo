import {GET_DEVICE_SUCCESS, BACK_TO_DEVICE_SELECTION} from '../actionConstants/devices';
import { history } from '../routers/AppRouter';

export function getDeviceSuccess(device) {
    return {
        type: GET_DEVICE_SUCCESS,
        device
    }
}

export function backToDeviceSelection() {    
    history.push('/');
    return {
        type: BACK_TO_DEVICE_SELECTION,        
    }
}

export function getDevice() {
    return async dispatch => {
        const device = await navigator.bluetooth.requestDevice({
            filters: [{ name: "AdAstra Evo" }]
        });
        dispatch(getDeviceSuccess(device));
        history.push('/app');
    };
  }