/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
  k_p = Kpi;
  k_d = Kdi;
  k_i = Kii;

  output_limit_max = output_lim_maxi;
  output_limit_min = output_lim_mini;

  error_p = 0.0;
  error_d = 0.0;
  error_i = 0.0;

  dt = 0.0;

}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/

  if (dt>0){
    error_d = (cte - error_p) / dt;
  } else {
    error_d = 0;
  }

  error_p = cte;
  error_i += cte * dt;

}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
    double control;

    // Compute control output according to PID controller
    control =  k_p * error_p + k_d * error_d + k_i * error_i;

    // Make sure control output is bounded to limits
    return max(min(output_limit_max, control), output_limit_min);
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
  dt = new_delta_time;
  return dt;
}