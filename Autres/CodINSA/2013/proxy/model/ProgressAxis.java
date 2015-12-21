/*   1:    */ package model;
/*   2:    */ 
/*   3:    */ import common.Copyable;
/*   4:    */ import common.Copyable.Context;
/*   5:    */ import common.Viewable;
/*   6:    */ import java.io.Serializable;
/*   7:    */ import java.util.Set;
/*   8:    */ 
/*   9:    */ public class ProgressAxis
/*  10:    */   extends Entity
/*  11:    */   implements Serializable, Viewable<View>
/*  12:    */ {
/*  13: 23 */   public double ratio2 = 0.0D;
/*  14: 23 */   public double ratio1 = 0.0D;
/*  15:    */   public final double length;
/*  16:    */   public final Oriented toBase2;
/*  17:    */   public final Oriented toBase1;
/*  18:    */   public final Base base2;
/*  19:    */   public final Base base1;
/*  20:    */   private static final long serialVersionUID = 1L;
/*  21:    */   
/*  22:    */   public ProgressAxis(int id, Base b1, Base b2)
/*  23:    */   {
/*  24: 31 */     super(id);
/*  25: 32 */     this.base1 = b1;
/*  26: 33 */     this.base2 = b2;
/*  27:    */     
/*  28: 35 */     this.toBase1 = new Oriented(b1);
/*  29: 36 */     this.toBase2 = new Oriented(b2);
/*  30: 37 */     b1.axes.add(this.toBase2);
/*  31: 38 */     b2.axes.add(this.toBase1);
/*  32: 39 */     this.length = b1.position().distanceTo(b2.position());
/*  33:    */   }
/*  34:    */   
/*  35:    */   public ProgressAxis(View src, Copyable.Context context)
/*  36:    */   {
/*  37: 43 */     super(src.id());
/*  38: 44 */     context.putSafe(src.model(), this);
/*  39: 45 */     this.base1 = src.base1().copied(context);
/*  40: 46 */     this.base2 = src.base2().copied(context);
/*  41:    */     
/*  42: 48 */     this.toBase1 = ((Oriented)context.getSafe(src.model().toBase1));
/*  43: 49 */     this.toBase2 = ((Oriented)context.getSafe(src.model().toBase2));
/*  44: 50 */     this.length = src.length();
/*  45:    */   }
/*  46:    */   
/*  47:    */   public ProgressAxis copy(Copyable.Context context)
/*  48:    */   {
/*  49: 64 */     if (context.containsKey(this)) {
/*  50: 65 */       return (ProgressAxis)context.getSafe(this);
/*  51:    */     }
/*  52: 66 */     ProgressAxis ret = new ProgressAxis(view(), context);
/*  53: 67 */     return ret;
/*  54:    */   }
/*  55:    */   
/*  56:    */   public int ownerId()
/*  57:    */   {
/*  58: 72 */     return this.base1.ownerId() == this.base2.ownerId() ? this.base1.ownerId() : 0;
/*  59:    */   }
/*  60:    */   
/*  61:    */   public Oriented arcTo(Base b)
/*  62:    */   {
/*  63: 76 */     if (b == this.base1) {
/*  64: 77 */       return this.toBase1;
/*  65:    */     }
/*  66: 78 */     if (b == this.base2) {
/*  67: 79 */       return this.toBase2;
/*  68:    */     }
/*  69: 80 */     throw new IllegalArgumentException();
/*  70:    */   }
/*  71:    */   
/*  72:    */   private Oriented mkOriented(Base next)
/*  73:    */   {
/*  74: 84 */     return new Oriented(next);
/*  75:    */   }
/*  76:    */   
/*  77:    */   public static abstract interface Nothing {}
/*  78:    */   
/*  79:    */   public final class Occidented
/*  80:    */     implements ProgressAxis.Nothing
/*  81:    */   {
/*  82:    */     public Occidented() {}
/*  83:    */   }
/*  84:    */   
/*  85:    */   public class Oriented
/*  86:    */     implements Copyable
/*  87:    */   {
/*  88:    */     final Base next;
/*  89:    */     
/*  90:    */     public Oriented(Base next)
/*  91:    */     {
/*  92: 92 */       this.next = next;
/*  93:    */     }
/*  94:    */     
/*  95:    */     public final Base.FullView next()
/*  96:    */     {
/*  97: 98 */       return this.next.view();
/*  98:    */     }
/*  99:    */     
/* 100:    */     public ProgressAxis.View axis()
/* 101:    */     {
/* 102:103 */       return ProgressAxis.this.view();
/* 103:    */     }
/* 104:    */     
/* 105:    */     public double ratio()
/* 106:    */     {
/* 107:109 */       if (this.next == ProgressAxis.this.base2) {
/* 108:110 */         return ProgressAxis.this.ratio1;
/* 109:    */       }
/* 110:111 */       assert (this.next == ProgressAxis.this.base1);
/* 111:112 */       return ProgressAxis.this.ratio2;
/* 112:    */     }
/* 113:    */     
/* 114:    */     void ratio(double val)
/* 115:    */     {
/* 116:115 */       if (this.next == ProgressAxis.this.base2)
/* 117:    */       {
/* 118:116 */         ProgressAxis.this.ratio1 = val;
/* 119:    */       }
/* 120:    */       else
/* 121:    */       {
/* 122:118 */         assert (this.next == ProgressAxis.this.base1);
/* 123:119 */         ProgressAxis.this.ratio2 = val;
/* 124:    */       }
/* 125:    */     }
/* 126:    */     
/* 127:    */     public Oriented opposite()
/* 128:    */     {
/* 129:123 */       if (this.next == ProgressAxis.this.base2) {
/* 130:124 */         return ProgressAxis.this.toBase1;
/* 131:    */       }
/* 132:125 */       assert (this.next == ProgressAxis.this.base1);
/* 133:126 */       return ProgressAxis.this.toBase2;
/* 134:    */     }
/* 135:    */     
/* 136:    */     public Oriented copy(Copyable.Context context)
/* 137:    */     {
/* 138:134 */       if (context.containsKey(this)) {
/* 139:135 */         return (Oriented)context.getSafe(this);
/* 140:    */       }
/* 141:141 */       Oriented ret = ProgressAxis.this.copy(context).mkOriented(this.next.copy(context));
/* 142:    */       
/* 143:143 */       context.putSafe(this, ret);
/* 144:    */       
/* 145:145 */       return ret;
/* 146:    */     }
/* 147:    */   }
/* 148:    */   
/* 149:    */   public class View
/* 150:    */     extends Entity.View
/* 151:    */   {
/* 152:    */     public View()
/* 153:    */     {
/* 154:160 */       super();
/* 155:    */     }
/* 156:    */     
/* 157:    */     public Base.FullView base1()
/* 158:    */     {
/* 159:164 */       return ProgressAxis.this.base1.view();
/* 160:    */     }
/* 161:    */     
/* 162:    */     public Base.FullView base2()
/* 163:    */     {
/* 164:168 */       return ProgressAxis.this.base2.view();
/* 165:    */     }
/* 166:    */     
/* 167:    */     public double ratio1()
/* 168:    */     {
/* 169:173 */       return ProgressAxis.this.ratio1;
/* 170:    */     }
/* 171:    */     
/* 172:    */     public double ratio2()
/* 173:    */     {
/* 174:178 */       return ProgressAxis.this.ratio2;
/* 175:    */     }
/* 176:    */     
/* 177:    */     public double length()
/* 178:    */     {
/* 179:183 */       return ProgressAxis.this.length;
/* 180:    */     }
/* 181:    */     
/* 182:    */     ProgressAxis copied(Copyable.Context context)
/* 183:    */     {
/* 184:186 */       return ProgressAxis.this.copy(context);
/* 185:    */     }
/* 186:    */     
/* 187:    */     protected ProgressAxis model()
/* 188:    */     {
/* 189:189 */       return ProgressAxis.this;
/* 190:    */     }
/* 191:    */   }
/* 192:    */   
/* 193:    */   public View view()
/* 194:    */   {
/* 195:194 */     return new View();
/* 196:    */   }
/* 197:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     model.ProgressAxis
 * JD-Core Version:    0.7.0.1
 */