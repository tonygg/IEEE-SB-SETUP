/*
 *  Little Green BATS (2008), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	November 1, 2008
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef _BATS_SIMPLELOCALIZER_HH_
#define _BATS_SIMPLELOCALOZER_HH_

#include "../localizer.hh"
#include "../../Distribution/NormalDistribution/normaldistribution.hh"

namespace bats
{

  class SimpleLocalizer : public Localizer
  {
      friend class Singleton<Localizer>;
      
      Eigen::Transform3d d_localTransform;
      Eigen::Transform3d d_globalTransform;
      
      rf<NormalDistribution> d_locationsRaw[Types::NOBJECTS];
      rf<NormalDistribution> d_locationsLocal[Types::NOBJECTS];
      rf<NormalDistribution> d_locationsGlobal[Types::NOBJECTS];
      
      rf<NormalDistribution> d_velocitiesLocal[Types::NOBJECTS];
      rf<NormalDistribution> d_velocitiesGlobal[Types::NOBJECTS];
      
      SimpleLocalizer();
      SimpleLocalizer(SimpleLocalizer const& other); //NI
      SimpleLocalizer& operator=(SimpleLocalizer const* other); //NI

    public:
      virtual void init() {}
      
      virtual void update();

      virtual bool alive(Types::Object object) const {return true;}

      /** Return whether the  object is visible */
      virtual bool visible(Types::Object object) const {return true;}

      /** Get the last localization time */
      virtual double time() {return 0;}
      /** Get the delay seen in the object observation */
      virtual double perceptionDelay (Types::Object object) {return 0;}
      /** Get the last update of the object */
      virtual double getObjectLastUpdate (Types::Object object) {return 0;}

      /** Return whether the information about the object is reliable */
      virtual bool isReliableLocal(Types::Object object) const {return true;}
      
      /** Return whether the information about the object is reliable */
      virtual bool isReliableGlobal(Types::Object object) const {return true;}

      virtual Eigen::Vector3d getObjectMovement (Types::Object object) {return Eigen::Vector3d();}
      
      virtual rf<Distribution> getLocationLocal(Types::Object object) { return d_locationsLocal[object]; }
      virtual rf<Distribution> getVelocityLocal(Types::Object object) { return d_velocitiesLocal[object]; }

      virtual rf<Distribution> getLocationGlobal(Types::Object object) { return d_locationsGlobal[object]; }
      virtual rf<Distribution> getVelocityGlobal(Types::Object object) { return d_velocitiesGlobal[object]; }
      

      virtual Eigen::Transform3d getLocalTransformation() const { return d_localTransform; }
      virtual Eigen::Transform3d getGlobalTransformation() const { return d_globalTransform; }

      // Needed when having fixed sized Eigen member
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  };
}

#endif

