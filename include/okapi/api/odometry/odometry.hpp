/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

#include "okapi/api/chassis/controller/chassisScales.hpp"
#include "okapi/api/chassis/model/readOnlyChassisModel.hpp"
#include "okapi/api/util/abstractRate.hpp"
#include "okapi/api/util/logging.hpp"
#include <atomic>
#include <memory>
#include <valarray>

namespace okapi {
struct OdomState {
  QLength x{0_m};
  QLength y{0_m};
  QAngle theta{0_deg};
};

class Odometry {
  public:
  /**
   * Odometry. Tracks the movement of the robot and estimates its position in coordinates
   * relative to the start (assumed to be (0, 0)).
   *
   * @param imodel The chassis model for reading sensors.
   * @param ichassisScales The chassis dimensions.
   * @param irate The rate.
   */
  Odometry(const std::shared_ptr<ReadOnlyChassisModel> &imodel,
           const ChassisScales &ichassisScales,
           std::unique_ptr<AbstractRate> irate,
           const std::shared_ptr<Logger> &ilogger = std::make_shared<Logger>());

  virtual ~Odometry() = default;

  /**
   * Sets the drive and turn scales.
   */
  virtual void setScales(const ChassisScales &ichassisScales);

  /**
   * Do one odometry step.
   */
  virtual void step();

  /**
   * Returns the current state.
   *
   * @return current state
   */
  virtual OdomState getState() const;

  /**
   * Sets a new state to be the current state.
   *
   * @param istate new state
   */
  virtual void setState(const OdomState &istate);

  protected:
  std::shared_ptr<Logger> logger;
  std::shared_ptr<ReadOnlyChassisModel> model;
  std::unique_ptr<AbstractRate> rate;
  OdomState state;
  ChassisScales chassisScales;
  std::valarray<std::int32_t> newTicks{0, 0}, tickDiff{0, 0}, lastTicks{0, 0};
  QLength mm{0_m};
};
} // namespace okapi
