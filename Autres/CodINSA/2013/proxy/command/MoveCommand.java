/*  1:   */ package command;
/*  2:   */ 
/*  3:   */ import common.Immutable;
/*  4:   */ import common.Util;
/*  5:   */ import model.Coord.Unique;
/*  6:   */ import model.Coord.View;
/*  7:   */ import model.Plane.FullView;
/*  8:   */ 
/*  9:   */ public class MoveCommand
/* 10:   */   extends Command
/* 11:   */ {
/* 12:   */   public final Plane.FullView plane;
/* 13:   */   public final Immutable<Coord.View> destination;
/* 14:   */   
/* 15:   */   public MoveCommand(Plane.FullView p, Coord.View d)
/* 16:   */   {
/* 17:22 */     Util.checkNull(new Object[] {p, d });
/* 18:23 */     this.plane = p;
/* 19:24 */     this.destination = new Immutable(new Coord.Unique(d));
/* 20:   */   }
/* 21:   */   
/* 22:   */   public String toString()
/* 23:   */   {
/* 24:30 */     return "mv " + this.plane.id() + " -> " + this.destination;
/* 25:   */   }
/* 26:   */   
/* 27:   */   public void match()
/* 28:   */     throws MoveCommand
/* 29:   */   {
/* 30:35 */     throw this;
/* 31:   */   }
/* 32:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     command.MoveCommand
 * JD-Core Version:    0.7.0.1
 */