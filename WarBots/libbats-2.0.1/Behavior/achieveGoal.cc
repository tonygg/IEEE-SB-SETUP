#include "behavior.ih"

bool Behavior::achieveGoal()
{
  behavior_signal(new AchieveGoalStartEvent(d_name, d_id));
  
  string msg;
  
  try {
    if (!d_tree)
      return true;
    
    bool succes = true;

		if (d_childrenCommitted)
		{
      succes = doLastChosen();
      msg = succes ? ": doLastChosen: succes" : ": doLastChosen: fail";
      behavior_signal(new BehaviorEvent(d_name, d_id, msg));
    }
    else
    {
      d_lastChosen.clear();
      succes = false;
      
      // Try slots in next sequence step (if there is a step left and we are not committed)
      if (d_curStep >= 0)
      {
        double prevStepStart = d_curStepStart;
        d_curStepStart = SClock::getInstance().getTime();
        succes = doNextStep();
        msg = succes ? ": doNextStep: succes" : ": fail";
        behavior_signal(new BehaviorEvent(d_name, d_id, msg));
        if (!succes)
          d_curStepStart = prevStepStart;
      }
      else
      {
        d_curStep = 0;
        d_curStepStart = SClock::getInstance().getTime();
      }
        
      if (!succes)
      {
        succes = doCurrentStep();
        msg = succes ? ": doCurrentStep: succes" : ": fail";
        behavior_signal(new BehaviorEvent(d_name, d_id, msg));
      }
    }
    return succes;

  } catch (BatsException *e) {
    BATS_CATCH_FRAME(e);
  }
  d_reset = false;
}

