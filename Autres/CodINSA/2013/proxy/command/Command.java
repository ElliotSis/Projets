package command;

public abstract class Command
  extends Throwable
{
  private static final long serialVersionUID = 1L;
  public static final int SUCCESS = 0;
  public static final int WARNING_COMMAND = -1;
  public static final int ERROR_COMMAND = -2;
  public static final int ERROR_TIME_OUT = -3;
  public static final int ERROR_FORBIDDEN = -4;
  public static final int ERROR_UNKNOWN = -5;
  
  public abstract void match()
    throws MoveCommand, LandCommand, WaitCommand, AttackCommand, FollowCommand, DropMilitarsCommand, FillFuelTankCommand, ExchangeResourcesCommand, BuildPlaneCommand, CancelRequestCommand;
}


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     command.Command
 * JD-Core Version:    0.7.0.1
 */