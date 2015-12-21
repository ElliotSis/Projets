/*  1:   */ package command;
/*  2:   */ 
/*  3:   */ import common.Util;
/*  4:   */ import model.Plane.FullView;
/*  5:   */ 
/*  6:   */ public class WaitCommand
/*  7:   */   extends Command
/*  8:   */ {
/*  9:   */   public final Plane.FullView plane;
/* 10:   */   
/* 11:   */   public WaitCommand(Plane.FullView p)
/* 12:   */   {
/* 13:14 */     Util.checkNull(p);
/* 14:15 */     this.plane = p;
/* 15:   */   }
/* 16:   */   
/* 17:   */   public String toString()
/* 18:   */   {
/* 19:20 */     return "wait " + this.plane.id();
/* 20:   */   }
/* 21:   */   
/* 22:   */   public void match()
/* 23:   */     throws WaitCommand
/* 24:   */   {
/* 25:25 */     throw this;
/* 26:   */   }
/* 27:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     command.WaitCommand
 * JD-Core Version:    0.7.0.1
 */