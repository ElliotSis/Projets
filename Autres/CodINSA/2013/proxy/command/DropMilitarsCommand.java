/*  1:   */ package command;
/*  2:   */ 
/*  3:   */ import common.Util;
/*  4:   */ import model.AbstractBase.View;
/*  5:   */ import model.Plane.FullView;
/*  6:   */ 
/*  7:   */ public class DropMilitarsCommand
/*  8:   */   extends Command
/*  9:   */ {
/* 10:   */   public final Plane.FullView planeSrc;
/* 11:   */   public final AbstractBase.View baseTarget;
/* 12:   */   public final double quantity;
/* 13:   */   
/* 14:   */   public DropMilitarsCommand(Plane.FullView p, AbstractBase.View b, double ndrop)
/* 15:   */   {
/* 16:20 */     Util.checkNull(new Object[] {p, b });
/* 17:21 */     this.planeSrc = p;
/* 18:22 */     this.baseTarget = b;
/* 19:23 */     this.quantity = ndrop;
/* 20:   */   }
/* 21:   */   
/* 22:   */   public String toString()
/* 23:   */   {
/* 24:28 */     return "drop " + this.planeSrc.id() + " --(" + this.quantity + ")--> " + this.baseTarget.id();
/* 25:   */   }
/* 26:   */   
/* 27:   */   public void match()
/* 28:   */     throws DropMilitarsCommand
/* 29:   */   {
/* 30:33 */     throw this;
/* 31:   */   }
/* 32:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     command.DropMilitarsCommand
 * JD-Core Version:    0.7.0.1
 */