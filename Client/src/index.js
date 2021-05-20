import React from 'react';
import ReactDOM from 'react-dom';
import { Provider } from 'react-redux'
import './index.css';
import AppRouter, {  } from './routers/AppRouter';
import reportWebVitals from './reportWebVitals';
import store from './store';

import LoadingPage from './screens/LoadingScreen';


const jsx = (
  <React.StrictMode>
      <Provider store={store}>
        <AppRouter />
      </Provider>
  </React.StrictMode>
);

let hasRendered = false;
const renderApp = () => {
  if (!hasRendered) {
    ReactDOM.render(jsx, document.getElementById('root'));
    hasRendered = true;
  }
};

ReactDOM.render(<LoadingPage />, document.getElementById('root'));

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();

renderApp();



