/*  1:   */ package model;
/*  2:   */ 
/*  3:   */ import common.Copyable.Context;
/*  4:   */ import common.Immutable;
/*  5:   */ import common.ListView;
/*  6:   */ import common.Unique;
/*  7:   */ import common.Util;
/*  8:   */ import java.util.ArrayList;
/*  9:   */ import java.util.List;
/* 10:   */ 
/* 11:   */ public abstract class AbstractBase
/* 12:   */   extends MaterialEntity
/* 13:   */ {
/* 14:   */   public final List<Plane> planes;
/* 15:   */   public final Immutable<Coord.View> position;
/* 16:   */   
/* 17:   */   public abstract class View
/* 18:   */     extends MaterialEntity.View
/* 19:   */   {
/* 20:   */     public View()
/* 21:   */     {
/* 22:18 */       super();
/* 23:   */     }
/* 24:   */     
/* 25:   */     public Immutable<Coord.View> getPosition()
/* 26:   */     {
/* 27:23 */       return AbstractBase.this.position;
/* 28:   */     }
/* 29:   */     
/* 30:   */     private ListView<Plane.FullView> planes()
/* 31:   */     {
/* 32:30 */       return AbstractBase.this.planes();
/* 33:   */     }
/* 34:   */     
/* 35:   */     abstract AbstractBase copied(Copyable.Context paramContext);
/* 36:   */   }
/* 37:   */   
/* 38:   */   public ListView<Plane.FullView> planes()
/* 39:   */   {
/* 40:40 */     return Util.view(this.planes);
/* 41:   */   }
/* 42:   */   
/* 43:   */   public abstract View view();
/* 44:   */   
/* 45:   */   public AbstractBase(View src, Copyable.Context context)
/* 46:   */   {
/* 47:48 */     super(src);
/* 48:49 */     context.putSafe(src.model(), this);
/* 49:50 */     this.planes = new ArrayList();
/* 50:51 */     for (Plane.FullView p : src.planes()) {
/* 51:52 */       this.planes.add(p.copied(context));
/* 52:   */     }
/* 53:54 */     this.position = src.getPosition();
/* 54:55 */     this.radarRange = src.radarRange();
/* 55:   */   }
/* 56:   */   
/* 57:   */   public AbstractBase(int id, Unique<Coord> pos)
/* 58:   */   {
/* 59:59 */     super(id);
/* 60:   */     
/* 61:61 */     this.position = new Immutable(pos);
/* 62:62 */     this.planes = new ArrayList();
/* 63:   */   }
/* 64:   */   
/* 65:   */   public Coord.View position()
/* 66:   */   {
/* 67:68 */     return (Coord.View)this.position.view();
/* 68:   */   }
/* 69:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     model.AbstractBase
 * JD-Core Version:    0.7.0.1
 */