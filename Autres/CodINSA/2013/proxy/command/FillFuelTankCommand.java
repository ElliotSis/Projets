/*  1:   */ package command;
/*  2:   */ 
/*  3:   */ import common.Util;
/*  4:   */ import model.Plane.FullView;
/*  5:   */ 
/*  6:   */ public class FillFuelTankCommand
/*  7:   */   extends Command
/*  8:   */ {
/*  9:   */   public final Plane.FullView planeSrc;
/* 10:   */   public final double quantity;
/* 11:   */   
/* 12:   */   public FillFuelTankCommand(Plane.FullView p, double qf)
/* 13:   */   {
/* 14:16 */     Util.checkNull(p);
/* 15:17 */     this.planeSrc = p;
/* 16:18 */     this.quantity = qf;
/* 17:   */   }
/* 18:   */   
/* 19:   */   public String toString()
/* 20:   */   {
/* 21:23 */     return "store " + this.planeSrc.id() + " :> " + this.quantity;
/* 22:   */   }
/* 23:   */   
/* 24:   */   public void match()
/* 25:   */     throws FillFuelTankCommand
/* 26:   */   {
/* 27:28 */     throw this;
/* 28:   */   }
/* 29:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     command.FillFuelTankCommand
 * JD-Core Version:    0.7.0.1
 */