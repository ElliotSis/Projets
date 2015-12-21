/*  1:   */ package command;
/*  2:   */ 
/*  3:   */ import common.Util;
/*  4:   */ import model.Plane.BasicView;
/*  5:   */ import model.Plane.FullView;
/*  6:   */ 
/*  7:   */ public class FollowCommand
/*  8:   */   extends Command
/*  9:   */ {
/* 10:   */   public final Plane.FullView planeSrc;
/* 11:   */   public final Plane.BasicView planeTarget;
/* 12:   */   
/* 13:   */   public FollowCommand(Plane.FullView p, Plane.BasicView t)
/* 14:   */   {
/* 15:16 */     Util.checkNull(new Object[] {p, t });
/* 16:17 */     this.planeSrc = p;
/* 17:18 */     this.planeTarget = t;
/* 18:   */   }
/* 19:   */   
/* 20:   */   public String toString()
/* 21:   */   {
/* 22:23 */     return "follow " + this.planeSrc.id() + " -> " + this.planeTarget.id();
/* 23:   */   }
/* 24:   */   
/* 25:   */   public void match()
/* 26:   */     throws FollowCommand
/* 27:   */   {
/* 28:28 */     throw this;
/* 29:   */   }
/* 30:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     command.FollowCommand
 * JD-Core Version:    0.7.0.1
 */