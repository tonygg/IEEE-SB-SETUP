#include "trainersocketcomm.ih"

void TrainerSocketComm::setBallPos(Vector3d const& pos)
{
  send(makeSetBallPosMessage(pos));
}

rf<Predicate> TrainerSocketComm::makeSetBallPosMessage(Vector3d const& pos)
{
  rf<Predicate> msg = new Predicate("ball");
  rf<Predicate> posPred = rf_cast<Predicate>(msg->addChild(new Predicate("pos")));
  posPred->pushLeafs(pos);
  return msg;
}

