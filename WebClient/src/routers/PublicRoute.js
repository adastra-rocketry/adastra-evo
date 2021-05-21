import React from 'react';
import { connect } from 'react-redux';
import { Route, Redirect } from 'react-router-dom';

export const PublicRoute = ({
  hasDeviceSelected,
  component: Component,
  ...rest
}) => (
    <Route {...rest} component={(props) => (
        hasDeviceSelected ? (
        <Redirect to="/app" />
      ) : (
        <Component {...props} />
      )
    )} />
  );

const mapStateToProps = (state) => ({
  hasDeviceSelected: !!state.device.selected
});

export default connect(mapStateToProps)(PublicRoute);
