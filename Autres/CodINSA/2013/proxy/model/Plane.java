/*   1:    */ package model;
/*   2:    */ 
/*   3:    */ import common.Copyable.Context;
/*   4:    */ import common.Unique;
/*   5:    */ import common.Viewable;
/*   6:    */ import java.io.Serializable;
/*   7:    */ import java.util.ArrayList;
/*   8:    */ import java.util.List;
/*   9:    */ 
/*  10:    */ public class Plane
/*  11:    */   extends MovingEntity
/*  12:    */   implements Serializable, Viewable<FullView>
/*  13:    */ {
/*  14:    */   private static final long serialVersionUID = 1L;
/*  15:    */   public final Type type;
/*  16:    */   public State state;
/*  17:    */   public AbstractBase curBase;
/*  18:    */   public double health;
/*  19:    */   public double militaryInHold;
/*  20:    */   public double fuelInHold;
/*  21:    */   public double fuelInTank;
/*  22:    */   public final FullView fullView;
/*  23:    */   public final BasicView basicView;
/*  24:    */   
/*  25:    */   public class FullView
/*  26:    */     extends Plane.BasicView
/*  27:    */   {
/*  28:    */     public FullView()
/*  29:    */     {
/*  30: 52 */       super();
/*  31:    */     }
/*  32:    */     
/*  33:    */     private FullView(boolean ignoreSync)
/*  34:    */     {
/*  35: 53 */       super();this.ignoreSync = ignoreSync;
/*  36:    */     }
/*  37:    */     
/*  38:    */     public FullView asLastViewed()
/*  39:    */     {
/*  40: 56 */       return new FullView(Plane.this, true);
/*  41:    */     }
/*  42:    */     
/*  43:    */     public Plane.State state()
/*  44:    */       throws OutOfSyncException
/*  45:    */     {
/*  46: 61 */       checkSynx(Plane.this.exists);return Plane.this.state;
/*  47:    */     }
/*  48:    */     
/*  49:    */     public AbstractBase.View curBase()
/*  50:    */       throws OutOfSyncException
/*  51:    */     {
/*  52: 66 */       checkSynx(Plane.this.exists);return Plane.this.curBase == null ? null : Plane.this.curBase.view();
/*  53:    */     }
/*  54:    */     
/*  55:    */     public double militaryInHold()
/*  56:    */       throws OutOfSyncException
/*  57:    */     {
/*  58: 71 */       checkSynx(Plane.this.exists);return Plane.this.militaryInHold;
/*  59:    */     }
/*  60:    */     
/*  61:    */     public double fuelInHold()
/*  62:    */       throws OutOfSyncException
/*  63:    */     {
/*  64: 75 */       checkSynx(Plane.this.exists);return Plane.this.fuelInHold;
/*  65:    */     }
/*  66:    */     
/*  67:    */     public double fuelInTank()
/*  68:    */       throws OutOfSyncException
/*  69:    */     {
/*  70: 80 */       checkSynx(Plane.this.exists);return Plane.this.fuelInTank;
/*  71:    */     }
/*  72:    */     
/*  73:    */     public double health()
/*  74:    */       throws OutOfSyncException
/*  75:    */     {
/*  76: 88 */       checkSynx(Plane.this.exists);return Plane.this.health;
/*  77:    */     }
/*  78:    */     
/*  79:    */     public boolean isWithinRadar(Coord.View pos)
/*  80:    */       throws OutOfSyncException
/*  81:    */     {
/*  82: 99 */       checkSynx(Plane.this.exists);
/*  83:100 */       return this.position.squareDistanceTo(pos) <= Plane.this.radarRange * Plane.this.radarRange;
/*  84:    */     }
/*  85:    */     
/*  86:    */     Plane copied(Copyable.Context context)
/*  87:    */     {
/*  88:106 */       return Plane.this.copy(context);
/*  89:    */     }
/*  90:    */     
/*  91:    */     public boolean knowsPositionOf(MaterialEntity.View e)
/*  92:    */       throws OutOfSyncException
/*  93:    */     {
/*  94:114 */       checkSynx(Plane.this.exists);
/*  95:115 */       if ((e instanceof Base.BasicView)) {
/*  96:116 */         return true;
/*  97:    */       }
/*  98:117 */       return (isFriend(e)) || (canSee(e));
/*  99:    */     }
/* 100:    */     
/* 101:    */     public boolean canSee(MaterialEntity.View e)
/* 102:    */       throws OutOfSyncException
/* 103:    */     {
/* 104:126 */       checkSynx(Plane.this.exists);
/* 105:127 */       if (((e instanceof FullView)) && (((FullView)e).state() == Plane.State.AT_AIRPORT)) {
/* 106:128 */         return false;
/* 107:    */       }
/* 108:129 */       return isWithinRadar(e.position);
/* 109:    */     }
/* 110:    */     
/* 111:    */     public boolean canAttack(Plane.BasicView e)
/* 112:    */       throws OutOfSyncException
/* 113:    */     {
/* 114:136 */       checkSynx(Plane.this.exists);
/* 115:137 */       return (canAttack()) && (isEnemy(e)) && (canSee(e));
/* 116:    */     }
/* 117:    */     
/* 118:    */     public String toString()
/* 119:    */     {
/* 120:144 */       return super.toString() + " state:" + state() + " fuel:" + fuelInHold() + " mil:" + militaryInHold();
/* 121:    */     }
/* 122:    */   }
/* 123:    */   
/* 124:    */   public class BasicView
/* 125:    */     extends MovingEntity.View
/* 126:    */   {
/* 127:    */     public BasicView()
/* 128:    */     {
/* 129:153 */       super();
/* 130:    */     }
/* 131:    */     
/* 132:    */     private BasicView(boolean ignoreSync)
/* 133:    */     {
/* 134:154 */       super();this.ignoreSync = ignoreSync;
/* 135:    */     }
/* 136:    */     
/* 137:    */     public boolean inSync()
/* 138:    */     {
/* 139:156 */       return Plane.this.exists;
/* 140:    */     }
/* 141:    */     
/* 142:    */     public BasicView asLastViewed()
/* 143:    */     {
/* 144:158 */       return new BasicView(Plane.this, true);
/* 145:    */     }
/* 146:    */     
/* 147:    */     protected String outOfSyncMsg()
/* 148:    */     {
/* 149:162 */       return "This plane no longer exists. Use method asLastViewed for an outdated view.";
/* 150:    */     }
/* 151:    */     
/* 152:    */     public double health()
/* 153:    */       throws OutOfSyncException
/* 154:    */     {
/* 155:168 */       checkSynx(Plane.this.exists);return Plane.this.health;
/* 156:    */     }
/* 157:    */     
/* 158:    */     public boolean canAttack()
/* 159:    */     {
/* 160:174 */       return this.type.firingRange > 0.0D;
/* 161:    */     }
/* 162:    */     
/* 163:180 */     public final Plane.Type type = Plane.this.type;
/* 164:    */     
/* 165:    */     public double radarRange()
/* 166:    */     {
/* 167:185 */       return Plane.this.radarRange;
/* 168:    */     }
/* 169:    */     
/* 170:    */     public String toString()
/* 171:    */     {
/* 172:190 */       return (exists() ? "" : "[dead] ") + "Plane " + id() + " owner:" + ownerId() + " health:" + health();
/* 173:    */     }
/* 174:    */   }
/* 175:    */   
/* 176:    */   public static enum State
/* 177:    */   {
/* 178:194 */     IDLE,  GOING_TO,  FOLLOWING,  ATTACKING,  DROPPING,  LANDING,  AT_AIRPORT,  DEAD;
/* 179:    */   }
/* 180:    */   
/* 181:    */   public FullView view()
/* 182:    */   {
/* 183:207 */     return this.fullView;
/* 184:    */   }
/* 185:    */   
/* 186:    */   public BasicView restrictedView()
/* 187:    */   {
/* 188:213 */     return this.basicView;
/* 189:    */   }
/* 190:    */   
/* 191:    */   public Plane(int id, Unique<Coord> pos, Type type)
/* 192:    */   {
/* 193:221 */     super(id, pos, new Coord.Unique(0.0D, 0.0D));
/* 194:    */     
/* 195:    */ 
/* 196:    */ 
/* 197:    */ 
/* 198:    */ 
/* 199:    */ 
/* 200:    */ 
/* 201:    */ 
/* 202:230 */     this.type = type;
/* 203:    */     
/* 204:232 */     this.health = type.fullHealth;
/* 205:233 */     this.radarRange = type.radarRange;
/* 206:234 */     this.fuelInTank = type.tankCapacity;
/* 207:235 */     this.fuelInHold = 0.0D;
/* 208:236 */     this.militaryInHold = 0.0D;
/* 209:    */     
/* 210:238 */     this.fullView = new FullView();
/* 211:239 */     this.basicView = new BasicView();
/* 212:    */   }
/* 213:    */   
/* 214:    */   public Plane(FullView src, Copyable.Context context)
/* 215:    */   {
/* 216:243 */     super(src = src.asLastViewed());
/* 217:244 */     context.putSafe(src.model(), this);
/* 218:245 */     this.health = src.health();
/* 219:246 */     this.state = src.state();
/* 220:247 */     this.radarRange = src.radarRange();
/* 221:    */     
/* 222:    */ 
/* 223:    */ 
/* 224:251 */     this.fuelInTank = src.fuelInTank();
/* 225:252 */     this.fuelInHold = src.fuelInHold();
/* 226:253 */     this.militaryInHold = src.militaryInHold();
/* 227:254 */     this.type = src.type;
/* 228:255 */     if (src.curBase() != null) {
/* 229:256 */       this.curBase = src.curBase().copied(context);
/* 230:    */     }
/* 231:258 */     this.fullView = new FullView();
/* 232:259 */     this.basicView = new BasicView();
/* 233:    */   }
/* 234:    */   
/* 235:    */   public Plane copy(Copyable.Context context)
/* 236:    */   {
/* 237:264 */     if (context.containsKey(this)) {
/* 238:266 */       return (Plane)context.getSafe(this);
/* 239:    */     }
/* 240:267 */     Plane ret = new Plane(view(), context);
/* 241:268 */     return ret;
/* 242:    */   }
/* 243:    */   
/* 244:    */   public boolean isFlying()
/* 245:    */   {
/* 246:272 */     return (this.state != State.AT_AIRPORT) && (this.state != State.DEAD);
/* 247:    */   }
/* 248:    */   
/* 249:    */   public void assignTo(AbstractBase b)
/* 250:    */   {
/* 251:277 */     unAssign();
/* 252:278 */     this.curBase = b;
/* 253:279 */     b.planes.add(this);
/* 254:280 */     assert (b.ownerId() == ownerId());
/* 255:    */   }
/* 256:    */   
/* 257:    */   public void unAssign()
/* 258:    */   {
/* 259:285 */     if (this.curBase != null)
/* 260:    */     {
/* 261:287 */       this.curBase.planes.remove(this);
/* 262:288 */       this.curBase = null;
/* 263:    */     }
/* 264:    */   }
/* 265:    */   
/* 266:    */   public static class Type
/* 267:    */   {
/* 268:295 */     public static double REGENERATION_SPEED = 0.1D;
/* 269:296 */     public static double FUEL_REFILL_SPEED = 0.1D;
/* 270:298 */     private static final List<Type> instances = new ArrayList();
/* 271:    */     public final int id;
/* 272:    */     public final double firingRange;
/* 273:    */     public final double radarRange;
/* 274:    */     public final double maxSpeed;
/* 275:    */     public final double maxRotSpeed;
/* 276:    */     public final double fullHealth;
/* 277:    */     public final double holdCapacity;
/* 278:    */     public final double tankCapacity;
/* 279:    */     public final double fuelConsumptionPerDistanceUnit;
/* 280:    */     public final double radius;
/* 281:    */     public final double timeToBuild;
/* 282:    */     public final double radarRange_squared;
/* 283:    */     
/* 284:    */     public static Type get(int id)
/* 285:    */     {
/* 286:301 */       return (Type)instances.get(id);
/* 287:    */     }
/* 288:    */     
/* 289:    */     private Type(double firingRange, double radarRange, double maxSpeed, double maxRotSpeed, double fullHealth, double holdCapacity, double tankCapacity, double fuelConsumptionPerDistanceUnit, double radius, double timeToBuild)
/* 290:    */     {
/* 291:341 */       this.id = instances.size();
/* 292:342 */       instances.add(this);
/* 293:    */       
/* 294:344 */       this.firingRange = firingRange;
/* 295:345 */       this.radarRange = radarRange;
/* 296:    */       
/* 297:347 */       this.maxSpeed = maxSpeed;
/* 298:348 */       this.maxRotSpeed = maxRotSpeed;
/* 299:    */       
/* 300:    */ 
/* 301:    */ 
/* 302:352 */       this.fullHealth = fullHealth;
/* 303:    */       
/* 304:354 */       this.holdCapacity = holdCapacity;
/* 305:355 */       this.tankCapacity = tankCapacity;
/* 306:    */       
/* 307:357 */       this.fuelConsumptionPerDistanceUnit = fuelConsumptionPerDistanceUnit;
/* 308:    */       
/* 309:359 */       this.radius = radius;
/* 310:360 */       this.timeToBuild = timeToBuild;
/* 311:    */       
/* 312:    */ 
/* 313:    */ 
/* 314:364 */       this.radarRange_squared = (radarRange * radarRange);
/* 315:    */     }
/* 316:    */     
/* 317:368 */     public static final Type MILITARY = new Type(
/* 318:    */     
/* 319:370 */       0.8D, 
/* 320:    */       
/* 321:372 */       0.9D, 
/* 322:    */       
/* 323:374 */       0.01D, 
/* 324:    */       
/* 325:376 */       0.09424777960769379D, 
/* 326:    */       
/* 327:378 */       100.0D, 
/* 328:    */       
/* 329:380 */       10.0D, 
/* 330:    */       
/* 331:382 */       10.0D, 
/* 332:    */       
/* 333:384 */       1.0D, 
/* 334:    */       
/* 335:386 */       0.03D, 
/* 336:    */       
/* 337:388 */       15.0D);
/* 338:391 */     public static final Type COMMERCIAL = new Type(
/* 339:    */     
/* 340:393 */       0.0D, 
/* 341:    */       
/* 342:395 */       MILITARY.radarRange, 
/* 343:    */       
/* 344:397 */       MILITARY.maxSpeed * 0.8D, 
/* 345:    */       
/* 346:399 */       MILITARY.maxRotSpeed * 0.7D, 
/* 347:    */       
/* 348:401 */       MILITARY.fullHealth * 4.0D, 
/* 349:    */       
/* 350:403 */       MILITARY.holdCapacity * 5.0D, 
/* 351:    */       
/* 352:405 */       MILITARY.tankCapacity * 4.0D, 
/* 353:    */       
/* 354:407 */       MILITARY.fuelConsumptionPerDistanceUnit * 2.0D, 
/* 355:    */       
/* 356:409 */       MILITARY.radius * 2.0D, 
/* 357:    */       
/* 358:411 */       150.0D);
/* 359:    */   }
/* 360:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     model.Plane
 * JD-Core Version:    0.7.0.1
 */