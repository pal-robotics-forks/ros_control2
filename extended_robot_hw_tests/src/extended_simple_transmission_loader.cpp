///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019, PAL Robotics S.L.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of PAL Robotics S.L. nor the names of its
//     contributors may be used to endorse or promote products derived from
//     this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

/// \author Jordán Palacios

#include <hardware_interface/internal/demangle_symbol.h>
#include <extended_robot_hw_tests/extended_simple_transmission.h>
#include <extended_robot_hw_tests/extended_simple_transmission_loader.h>

#include <pluginlib/class_list_macros.hpp>

#include <ros/console.h>

namespace transmission_interface
{
TransmissionSharedPtr ExtendedSimpleTransmissionLoader::load(const TransmissionInfo& transmission_info)
{
  // Transmission should contain only one actuator/joint
  if (!checkActuatorDimension(transmission_info, 1))
  {
    return TransmissionSharedPtr();
  }
  if (!checkJointDimension(transmission_info, 1))
  {
    return TransmissionSharedPtr();
  }

  // Parse actuator and joint xml elements
  TiXmlElement actuator_el = loadXmlElement(transmission_info.actuators_.front().xml_element_);
  TiXmlElement joint_el = loadXmlElement(transmission_info.joints_.front().xml_element_);

  // Parse required mechanical reduction
  double reduction = 0.0;
  const ParseStatus reduction_status = getActuatorReduction(
      actuator_el, transmission_info.actuators_.front().name_, transmission_info.name_,
      true,  // Required
      reduction);
  if (reduction_status != SUCCESS)
  {
    return TransmissionSharedPtr();
  }

  // Parse optional joint offset. Even though it's optional --and to avoid surprises-- we
  // fail if the element is specified but is of the wrong type
  double joint_offset = 0.0;
  const ParseStatus joint_offset_status =
      getJointOffset(joint_el, transmission_info.joints_.front().name_, transmission_info.name_,
                     false,  // Optional
                     joint_offset);
  if (joint_offset_status == BAD_TYPE)
  {
    return TransmissionSharedPtr();
  }

  // Transmission instance
  try
  {
    TransmissionSharedPtr transmission(new ExtendedSimpleTransmission(reduction, joint_offset));
    return transmission;
  }
  catch (const TransmissionInterfaceException& ex)
  {
    using hardware_interface::internal::demangledTypeName;
    ROS_ERROR_STREAM_NAMED("parser", "Failed to construct transmission '"
                                         << transmission_info.name_ << "' of type '"
                                         << demangledTypeName<ExtendedSimpleTransmission>()
                                         << "'. " << ex.what());
    return TransmissionSharedPtr();
  }
}

}  // namespace transmission_interface

PLUGINLIB_EXPORT_CLASS(transmission_interface::ExtendedSimpleTransmissionLoader,
                       transmission_interface::TransmissionLoader)
