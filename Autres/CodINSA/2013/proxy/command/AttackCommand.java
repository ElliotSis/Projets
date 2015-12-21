/*  1:   */ package command;
/*  2:   */ 
/*  3:   */ import common.Util;
/*  4:   */ import model.Plane.BasicView;
/*  5:   */ import model.Plane.FullView;
/*  6:   */ 
/*  7:   */ public class AttackCommand
/*  8:   */   extends Command
/*  9:   */ {
/* 10:   */   public final Plane.FullView planeSrc;
/* 11:   */   public final Plane.BasicView planeTarget;
/* 12:   */   
/* 13:   */   public AttackCommand(Plane.FullView self, Plane.BasicView target)
/* 14:   */   {
/* 15:20 */     Util.checkNull(new Object[] {self, target });
/* 16:   */     
/* 17:22 */     this.planeSrc = self;
/* 18:23 */     this.planeTarget = target;
/* 19:   */   }
/* 20:   */   
/* 21:   */   public String toString()
/* 22:   */   {
/* 23:28 */     return "attack " + this.planeSrc.id() + " -> " + this.planeTarget.id();
/* 24:   */   }
/* 25:   */   
/* 26:   */   public void match()
/* 27:   */     throws AttackCommand
/* 28:   */   {
/* 29:33 */     throw this;
/* 30:   */   }
/* 31:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     command.AttackCommand
 * JD-Core Version:    0.7.0.1
 */