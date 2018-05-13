//
// Created by sg on 18.04.18.
//

#include "CVillage.hpp"
CVillage::CVillage(const CurrentSerializerType &m_properties, const CPosition &m_position) : CObject(m_position,
                                                                                                     false,
                                                                                                     true,
                                                                                                     true,
                                                                                                     false,
                                                                                                     m_properties) {}
