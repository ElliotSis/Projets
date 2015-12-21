/*   1:    */ package model;
/*   2:    */ 
/*   3:    */ import common.Copyable;
/*   4:    */ import common.Copyable.Context;
/*   5:    */ import common.CopyableAs;
/*   6:    */ import common.Unique;
/*   7:    */ import common.Util;
/*   8:    */ import common.Util.Dummy;
/*   9:    */ import common.Viewable;
/*  10:    */ import common.Viewable.View;
/*  11:    */ import java.awt.geom.Point2D.Double;
/*  12:    */ 
/*  13:    */ public final class Coord
/*  14:    */   extends InternalView
/*  15:    */   implements Viewable<View>, Copyable
/*  16:    */ {
/*  17: 45 */   public static final View origin = new Coord(0.0D, 0.0D).view();
/*  18: 46 */   public static final View unit = new Coord(1.0D, 1.0D).view();
/*  19:    */   public double x;
/*  20:    */   public double y;
/*  21:    */   
/*  22:    */   public static Coord barycenter(View c1, View c2, double coeff)
/*  23:    */   {
/*  24: 50 */     Coord bary = c2.addedTo(c1, -1.0D);
/*  25: 51 */     bary.mult(coeff);
/*  26: 52 */     bary.add(c1);
/*  27: 53 */     return bary;
/*  28:    */   }
/*  29:    */   
/*  30:    */   public final class View
/*  31:    */     extends InternalView
/*  32:    */     implements Viewable.View, CopyableAs<Coord>
/*  33:    */   {
/*  34:    */     public View()
/*  35:    */     {
/*  36:142 */       this.model = Coord.this;
/*  37:    */     }
/*  38:    */     
/*  39:    */     public Coord copyAs(Util.Dummy<Coord> type)
/*  40:    */     {
/*  41:147 */       return new Coord(this);
/*  42:    */     }
/*  43:    */   }
/*  44:    */   
/*  45:    */   public static final class Unique
/*  46:    */     extends Unique<Coord>
/*  47:    */     implements Coord.Interface.ReadWrite, Viewable<Coord.View>
/*  48:    */   {
/*  49:    */     public Unique(Coord.View original)
/*  50:    */     {
/*  51:175 */       super();
/*  52:    */     }
/*  53:    */     
/*  54:    */     public Unique(double x, double y)
/*  55:    */     {
/*  56:178 */       super();
/*  57:    */     }
/*  58:    */     
/*  59:    */     public Unique(Unique<Coord> original)
/*  60:    */     {
/*  61:180 */       super();
/*  62:    */     }
/*  63:    */     
/*  64:    */     public Coord.View view()
/*  65:    */     {
/*  66:185 */       return (Coord.View)Util.view(this);
/*  67:    */     }
/*  68:    */     
/*  69:    */     public double x()
/*  70:    */     {
/*  71:190 */       return ((Coord)this.object).x;
/*  72:    */     }
/*  73:    */     
/*  74:    */     public double y()
/*  75:    */     {
/*  76:194 */       return ((Coord)this.object).y;
/*  77:    */     }
/*  78:    */     
/*  79:    */     public double norm()
/*  80:    */     {
/*  81:197 */       return ((Coord)this.object).norm();
/*  82:    */     }
/*  83:    */     
/*  84:    */     public Coord opposite()
/*  85:    */     {
/*  86:200 */       return ((Coord)this.object).opposite();
/*  87:    */     }
/*  88:    */     
/*  89:    */     public Coord addedTo(Coord.View cv)
/*  90:    */     {
/*  91:204 */       return ((Coord)this.object).addedTo(cv);
/*  92:    */     }
/*  93:    */     
/*  94:    */     public Coord addedTo(Coord.View cv, double coeff)
/*  95:    */     {
/*  96:208 */       return ((Coord)this.object).addedTo(cv);
/*  97:    */     }
/*  98:    */     
/*  99:    */     public Coord shifted(double shift)
/* 100:    */     {
/* 101:212 */       return ((Coord)this.object).shifted(shift);
/* 102:    */     }
/* 103:    */     
/* 104:    */     public Coord rotated(Coord.View center, double angle)
/* 105:    */     {
/* 106:216 */       return ((Coord)this.object).rotated(center, angle);
/* 107:    */     }
/* 108:    */     
/* 109:    */     public double distanceTo(Coord.View cv)
/* 110:    */     {
/* 111:220 */       return ((Coord)this.object).distanceTo(cv);
/* 112:    */     }
/* 113:    */     
/* 114:    */     public double squareDistanceTo(Coord.View cv)
/* 115:    */     {
/* 116:224 */       return squareDistanceTo(cv);
/* 117:    */     }
/* 118:    */     
/* 119:    */     public double angleWith(Coord.View cv)
/* 120:    */     {
/* 121:228 */       return ((Coord)this.object).angleWith(cv);
/* 122:    */     }
/* 123:    */     
/* 124:    */     public double x(double value)
/* 125:    */     {
/* 126:232 */       return ((Coord)this.object).x = value;
/* 127:    */     }
/* 128:    */     
/* 129:    */     public double y(double value)
/* 130:    */     {
/* 131:236 */       return ((Coord)this.object).y = value;
/* 132:    */     }
/* 133:    */     
/* 134:    */     public Coord copy(Copyable.Context context)
/* 135:    */     {
/* 136:240 */       return ((Coord)this.object).copy(context);
/* 137:    */     }
/* 138:    */     
/* 139:    */     public void set(Coord.View cv)
/* 140:    */     {
/* 141:244 */       ((Coord)this.object).set(cv);
/* 142:    */     }
/* 143:    */     
/* 144:    */     public void add(Coord.View cv)
/* 145:    */     {
/* 146:248 */       ((Coord)this.object).add(cv);
/* 147:    */     }
/* 148:    */     
/* 149:    */     public void sub(Coord.View cv)
/* 150:    */     {
/* 151:252 */       ((Coord)this.object).set(cv);
/* 152:    */     }
/* 153:    */     
/* 154:    */     public void shift(double shift)
/* 155:    */     {
/* 156:256 */       ((Coord)this.object).shift(shift);
/* 157:    */     }
/* 158:    */     
/* 159:    */     public void shift(double dx, double dy)
/* 160:    */     {
/* 161:260 */       ((Coord)this.object).shift(dx, dy);
/* 162:    */     }
/* 163:    */     
/* 164:    */     public void mult(double q)
/* 165:    */     {
/* 166:264 */       ((Coord)this.object).mult(q);
/* 167:    */     }
/* 168:    */     
/* 169:    */     public void rotate(Coord.View center, double angle)
/* 170:    */     {
/* 171:268 */       ((Coord)this.object).rotate(center, angle);
/* 172:    */     }
/* 173:    */   }
/* 174:    */   
/* 175:275 */   private final View view = new View();
/* 176:    */   
/* 177:    */   public View view()
/* 178:    */   {
/* 179:279 */     return this.view;
/* 180:    */   }
/* 181:    */   
/* 182:    */   public Coord copy(Copyable.Context context)
/* 183:    */   {
/* 184:285 */     return new Coord(this);
/* 185:    */   }
/* 186:    */   
/* 187:    */   public Coord(double x, double y)
/* 188:    */   {
/* 189:290 */     this.model = this;
/* 190:291 */     this.x = x;
/* 191:292 */     this.y = y;
/* 192:    */   }
/* 193:    */   
/* 194:    */   public Coord(View v)
/* 195:    */   {
/* 196:295 */     this(v.x(), v.y());
/* 197:    */   }
/* 198:    */   
/* 199:    */   public Coord(Coord c)
/* 200:    */   {
/* 201:298 */     this(c.view);
/* 202:    */   }
/* 203:    */   
/* 204:    */   public Coord(Point2D.Double p)
/* 205:    */   {
/* 206:301 */     this(p.x, p.y);
/* 207:    */   }
/* 208:    */   
/* 209:    */   public final void set(View cv)
/* 210:    */   {
/* 211:308 */     this.x = cv.x();
/* 212:309 */     this.y = cv.y();
/* 213:    */   }
/* 214:    */   
/* 215:    */   public final void add(View cv)
/* 216:    */   {
/* 217:313 */     this.x += cv.x();
/* 218:314 */     this.y += cv.y();
/* 219:    */   }
/* 220:    */   
/* 221:    */   public final void add(View cv, double coeff)
/* 222:    */   {
/* 223:318 */     this.x += cv.x() * coeff;
/* 224:319 */     this.y += cv.y() * coeff;
/* 225:    */   }
/* 226:    */   
/* 227:    */   public final void sub(View cv)
/* 228:    */   {
/* 229:323 */     this.x -= cv.x();
/* 230:324 */     this.y -= cv.y();
/* 231:    */   }
/* 232:    */   
/* 233:    */   public final void shift(double shift)
/* 234:    */   {
/* 235:327 */     this.x += shift;
/* 236:328 */     this.y += shift;
/* 237:    */   }
/* 238:    */   
/* 239:    */   public final void shift(double dx, double dy)
/* 240:    */   {
/* 241:331 */     this.x += dx;
/* 242:332 */     this.y += dy;
/* 243:    */   }
/* 244:    */   
/* 245:    */   public final void mult(double q)
/* 246:    */   {
/* 247:336 */     this.x *= q;
/* 248:337 */     this.y *= q;
/* 249:    */   }
/* 250:    */   
/* 251:    */   public void rotate(View center, double angle)
/* 252:    */   {
/* 253:346 */     throw new UnsupportedOperationException("Not implemented yet");
/* 254:    */   }
/* 255:    */   
/* 256:    */   public static abstract interface Interface
/* 257:    */   {
/* 258:    */     public static abstract interface ReadOnly
/* 259:    */     {
/* 260:    */       public abstract double x();
/* 261:    */       
/* 262:    */       public abstract double y();
/* 263:    */       
/* 264:    */       public abstract double norm();
/* 265:    */       
/* 266:    */       public abstract Coord opposite();
/* 267:    */       
/* 268:    */       public abstract Coord addedTo(Coord.View paramView);
/* 269:    */       
/* 270:    */       public abstract Coord addedTo(Coord.View paramView, double paramDouble);
/* 271:    */       
/* 272:    */       public abstract Coord shifted(double paramDouble);
/* 273:    */       
/* 274:    */       public abstract Coord rotated(Coord.View paramView, double paramDouble);
/* 275:    */       
/* 276:    */       public abstract double distanceTo(Coord.View paramView);
/* 277:    */       
/* 278:    */       public abstract double squareDistanceTo(Coord.View paramView);
/* 279:    */       
/* 280:    */       public abstract double angleWith(Coord.View paramView);
/* 281:    */     }
/* 282:    */     
/* 283:    */     public static abstract interface ReadWrite
/* 284:    */       extends Coord.Interface.ReadOnly
/* 285:    */     {
/* 286:    */       public abstract double x(double paramDouble);
/* 287:    */       
/* 288:    */       public abstract double y(double paramDouble);
/* 289:    */       
/* 290:    */       public abstract Coord.View view();
/* 291:    */       
/* 292:    */       public abstract Coord copy(Copyable.Context paramContext);
/* 293:    */       
/* 294:    */       public abstract void set(Coord.View paramView);
/* 295:    */       
/* 296:    */       public abstract void add(Coord.View paramView);
/* 297:    */       
/* 298:    */       public abstract void sub(Coord.View paramView);
/* 299:    */       
/* 300:    */       public abstract void shift(double paramDouble);
/* 301:    */       
/* 302:    */       public abstract void shift(double paramDouble1, double paramDouble2);
/* 303:    */       
/* 304:    */       public abstract void mult(double paramDouble);
/* 305:    */       
/* 306:    */       public abstract void rotate(Coord.View paramView, double paramDouble);
/* 307:    */     }
/* 308:    */   }
/* 309:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     model.Coord
 * JD-Core Version:    0.7.0.1
 */