/*   1:    */ package model;
/*   2:    */ 
/*   3:    */ import common.Copyable;
/*   4:    */ import common.Viewable.View;
/*   5:    */ 
/*   6:    */ public abstract class Entity
/*   7:    */   implements Copyable
/*   8:    */ {
/*   9:    */   public final int id;
/*  10: 11 */   public boolean exists = true;
/*  11: 12 */   public boolean isAiObject = false;
/*  12: 18 */   private int ownerId = 0;
/*  13:    */   
/*  14:    */   public class View
/*  15:    */     implements Viewable.View
/*  16:    */   {
/*  17: 25 */     protected boolean ignoreSync = false;
/*  18:    */     
/*  19:    */     public View() {}
/*  20:    */     
/*  21:    */     protected String outOfSyncMsg()
/*  22:    */     {
/*  23: 28 */       return "Entity out of sync";
/*  24:    */     }
/*  25:    */     
/*  26:    */     protected void checkSynx(boolean sync)
/*  27:    */       throws OutOfSyncException
/*  28:    */     {
/*  29: 32 */       if ((!sync) && (!this.ignoreSync)) {
/*  30: 33 */         throw new OutOfSyncException(outOfSyncMsg());
/*  31:    */       }
/*  32:    */     }
/*  33:    */     
/*  34:    */     public int id()
/*  35:    */     {
/*  36: 39 */       return Entity.this.id;
/*  37:    */     }
/*  38:    */     
/*  39:    */     public boolean exists()
/*  40:    */     {
/*  41: 43 */       return Entity.this.exists;
/*  42:    */     }
/*  43:    */     
/*  44:    */     public int ownerId()
/*  45:    */     {
/*  46: 47 */       return Entity.this.ownerId();
/*  47:    */     }
/*  48:    */     
/*  49:    */     public boolean isWithinRadar(Coord.View pos)
/*  50:    */     {
/*  51: 52 */       return false;
/*  52:    */     }
/*  53:    */     
/*  54:    */     public boolean isFriend(View e)
/*  55:    */     {
/*  56: 59 */       return ownerId() == e.ownerId();
/*  57:    */     }
/*  58:    */     
/*  59:    */     public final boolean isEnemy(View e)
/*  60:    */     {
/*  61: 67 */       return (ownerId() > 0) && (ownerId() != e.ownerId());
/*  62:    */     }
/*  63:    */     
/*  64:    */     protected Entity model()
/*  65:    */     {
/*  66: 70 */       return Entity.this;
/*  67:    */     }
/*  68:    */   }
/*  69:    */   
/*  70:    */   public boolean owned()
/*  71:    */   {
/*  72: 74 */     return ownerId() != 0;
/*  73:    */   }
/*  74:    */   
/*  75:    */   public Entity(int id)
/*  76:    */   {
/*  77: 80 */     this.id = id;
/*  78:    */   }
/*  79:    */   
/*  80:    */   public Entity(View src)
/*  81:    */   {
/*  82: 88 */     this(src.id());
/*  83: 89 */     this.ownerId = src.ownerId();
/*  84:    */   }
/*  85:    */   
/*  86:    */   public int ownerId()
/*  87:    */   {
/*  88: 94 */     return this.ownerId;
/*  89:    */   }
/*  90:    */   
/*  91:    */   public void ownerId(int id)
/*  92:    */   {
/*  93: 95 */     this.ownerId = id;
/*  94:    */   }
/*  95:    */   
/*  96:    */   public View view()
/*  97:    */   {
/*  98:107 */     return new View();
/*  99:    */   }
/* 100:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     model.Entity
 * JD-Core Version:    0.7.0.1
 */