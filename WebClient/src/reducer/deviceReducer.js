import {
  GET_DEVICE_SUCCESS,
  BACK_TO_DEVICE_SELECTION,
  DEVICE_CHARACTERISTIC_CHANGE_RECEIVED,
} from "../constants/devices";

function deviceReducers(
  state = {
    selected: null,
    server: null,
    currentDeviceState: {},
    service: null,
    currentDeviceStateCharacteristics: {
      currentDeviceState_MainData_Characteristic: null,
      currentDeviceState_AccData_Characteristic: null,
      currentDeviceState_GData_Characteristic: null,
      currentDeviceState_MagData_Characteristic: null,
      currentDeviceState_IMUData_Characteristic: null,
      currentDeviceState_PressureData_Characteristic: null,
      currentDeviceState_KalmanData_Characteristic: null,
    },
  },
  action
) {
  switch (action.type) {
    case GET_DEVICE_SUCCESS:
      const {
        device,
        server,
        service,
        currentDeviceState_MainData_Characteristic,
        currentDeviceState_AccData_Characteristic,
        currentDeviceState_GData_Characteristic,
        currentDeviceState_MagData_Characteristic,
        currentDeviceState_IMUData_Characteristic,
        currentDeviceState_PressureData_Characteristic,
        currentDeviceState_KalmanData_Characteristic,
      } = action;
      return {
        ...state,
        selected: device,
        server,
        service,
        currentDeviceStateCharacteristics: {
          currentDeviceState_MainData_Characteristic,
          currentDeviceState_AccData_Characteristic,
          currentDeviceState_GData_Characteristic,
          currentDeviceState_MagData_Characteristic,
          currentDeviceState_IMUData_Characteristic,
          currentDeviceState_PressureData_Characteristic,
          currentDeviceState_KalmanData_Characteristic,
        },
      };
    case BACK_TO_DEVICE_SELECTION:
      return {
        ...state,
        selected: null,
        server: null,
        currentDeviceState: {},
        service: null,
        currentDeviceStateCharacteristics: {
          currentDeviceState_MainData_Characteristic: null,
          currentDeviceState_AccData_Characteristic: null,
          currentDeviceState_GData_Characteristic: null,
          currentDeviceState_MagData_Characteristic: null,
          currentDeviceState_IMUData_Characteristic: null,
          currentDeviceState_PressureData_Characteristic: null,
          currentDeviceState_KalmanData_Characteristic: null,
        },
      };
    case DEVICE_CHARACTERISTIC_CHANGE_RECEIVED:
      let currentDeviceState = {
        ...state.currentDeviceState
      };
      currentDeviceState[action.name] = action.data;
      return {
        ...state,
        currentDeviceState
      };
    default:
      return state;
  }
}

export default deviceReducers;
