/*  1:   */ package command;
/*  2:   */ 
/*  3:   */ import common.Util;
/*  4:   */ import model.AbstractBase.View;
/*  5:   */ import model.Plane.FullView;
/*  6:   */ 
/*  7:   */ public class LandCommand
/*  8:   */   extends Command
/*  9:   */ {
/* 10:   */   public Plane.FullView plane;
/* 11:   */   public AbstractBase.View base;
/* 12:   */   
/* 13:   */   public LandCommand(Plane.FullView p, AbstractBase.View b)
/* 14:   */   {
/* 15:16 */     Util.checkNull(new Object[] {p, b });
/* 16:17 */     this.plane = p;
/* 17:18 */     this.base = b;
/* 18:   */   }
/* 19:   */   
/* 20:   */   public String toString()
/* 21:   */   {
/* 22:23 */     return "land " + this.plane.id() + " -> " + this.base.id();
/* 23:   */   }
/* 24:   */   
/* 25:   */   public void match()
/* 26:   */     throws LandCommand
/* 27:   */   {
/* 28:28 */     throw this;
/* 29:   */   }
/* 30:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     command.LandCommand
 * JD-Core Version:    0.7.0.1
 */