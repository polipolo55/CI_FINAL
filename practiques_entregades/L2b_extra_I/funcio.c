int detectEdge (int PORT_ant, int PORT_act, int pin, int edge)
{
  int mask = 1 << pin;

    if (edge == 1) 
    {
        if ((PORT_ant & mask) == 0 && (PORT_act & mask) != 0) return 1;
    }
    else
    {
        if ((PORT_ant & mask) != 0 && (PORT_act & mask) == 0) return 1;
    }

  return 0;
}