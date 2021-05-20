import {
  GET_DEVICE_SUCCESS,
  BACK_TO_DEVICE_SELECTION,
  DEVICE_CHARACTERISTIC_CHANGE_RECEIVED,
} from "../actionConstants/devices";

function deviceReducers(
  state = { selected: null, currentDeviceState: null },
  action
) {
  switch (action.type) {
    case GET_DEVICE_SUCCESS:
      const { device, server, service, currentDeviceStateCharacteristic } =
        action;
      return {
        ...state,
        selected: device,
        server,
        service,
        currentDeviceStateCharacteristic,
      };
    case BACK_TO_DEVICE_SELECTION:
      return {
        ...state,
        selected: null,
      };
    case DEVICE_CHARACTERISTIC_CHANGE_RECEIVED:
      return {
        ...state,
        currentDeviceState: action.data,
      };
    default:
      return state;
  }
}

export default deviceReducers;
