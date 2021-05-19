import React from 'react';
import { connect } from 'react-redux';
import { Route, Redirect } from 'react-router-dom';
import Header from '../components/Header';

export const PrivateRoute = ({
    hasDeviceSelected,
  component: Component,
  ...rest
}) => (
    <Route {...rest} component={(props) => (
        hasDeviceSelected ? (
        <div>
          <Header />
          <Component {...props} />
        </div>
      ) : (
          <Redirect to="/" />
        )
    )} />
  );

const mapStateToProps = (state) => ({
    hasDeviceSelected: !!state.device.selected
});

export default connect(mapStateToProps)(PrivateRoute);
