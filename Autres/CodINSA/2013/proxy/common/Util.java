/*   1:    */ package common;
/*   2:    */ 
/*   3:    */ import java.lang.reflect.InvocationTargetException;
/*   4:    */ import java.lang.reflect.Method;
/*   5:    */ import java.util.ArrayList;
/*   6:    */ import java.util.Collection;
/*   7:    */ import java.util.List;
/*   8:    */ import java.util.Map;
/*   9:    */ import java.util.Random;
/*  10:    */ import java.util.Set;
/*  11:    */ 
/*  12:    */ public class Util
/*  13:    */ {
/*  14: 18 */   public static final Random rand = new Random();
/*  15:    */   
/*  16:    */   public static final void checkNull(Object obj)
/*  17:    */   {
/*  18: 41 */     if (obj == null) {
/*  19: 44 */       throw new IllegalArgumentException(new NullPointerException("No null reference allowed"));
/*  20:    */     }
/*  21:    */   }
/*  22:    */   
/*  23:    */   public static final void checkNull(Object... objs)
/*  24:    */   {
/*  25: 47 */     Object[] arrayOfObject = objs;int j = objs.length;
/*  26: 47 */     for (int i = 0; i < j; i++)
/*  27:    */     {
/*  28: 47 */       Object obj = arrayOfObject[i];
/*  29: 48 */       checkNull(obj);
/*  30:    */     }
/*  31:    */   }
/*  32:    */   
/*  33:    */   public static final <T> Nullable<T>.View findFirst(CollectionView<T> from, Predicate<T> pred)
/*  34:    */   {
/*  35: 55 */     for (T t : from) {
/*  36: 56 */       if (((Boolean)pred.convert(t)).booleanValue()) {
/*  37: 57 */         return new Nullable(t).view();
/*  38:    */       }
/*  39:    */     }
/*  40: 58 */     return Nullable.NULL();
/*  41:    */   }
/*  42:    */   
/*  43:    */   public static final <T> Collection<T> findAll(CollectionView<T> from, Predicate<T> pred)
/*  44:    */   {
/*  45: 65 */     ArrayList<T> ret = new ArrayList();
/*  46: 66 */     for (T t : from) {
/*  47: 67 */       if (((Boolean)pred.convert(t)).booleanValue()) {
/*  48: 68 */         ret.add(t);
/*  49:    */       }
/*  50:    */     }
/*  51: 69 */     return ret;
/*  52:    */   }
/*  53:    */   
/*  54:    */   static Copyable.Context getContext(Copyable.Context context)
/*  55:    */   {
/*  56: 79 */     return context == null ? new Copyable.Context() : context;
/*  57:    */   }
/*  58:    */   
/*  59:    */   static Copyable.Context getContext()
/*  60:    */   {
/*  61: 81 */     return getContext(null);
/*  62:    */   }
/*  63:    */   
/*  64:    */   public static <T extends Copyable> T copy(T src, Copyable.Context context)
/*  65:    */   {
/*  66: 93 */     return (Copyable)src.copy(context);
/*  67:    */   }
/*  68:    */   
/*  69:    */   public static <T extends Copyable> T copy(T src)
/*  70:    */   {
/*  71:100 */     return copy(src, getContext());
/*  72:    */   }
/*  73:    */   
/*  74:    */   public static <T extends CopyableAs<R>, R> R copy(T src)
/*  75:    */   {
/*  76:108 */     return src.copyAs(new Dummy());
/*  77:    */   }
/*  78:    */   
/*  79:    */   public static <T extends Copyable> Copyable.Copier<List<T>> getListCopier()
/*  80:    */   {
/*  81:119 */     new Copyable.Copier()
/*  82:    */     {
/*  83:    */       public List<T> copy(List<T> src, Copyable.Context context)
/*  84:    */       {
/*  85:122 */         return (List)Util.copy(src, context);
/*  86:    */       }
/*  87:    */     };
/*  88:    */   }
/*  89:    */   
/*  90:    */   public static <T> Copyable.Copier<List<T>> getListCopier(Copyable.Copier<T> elementCopier)
/*  91:    */   {
/*  92:134 */     new Copyable.Copier()
/*  93:    */     {
/*  94:    */       public List<T> copy(List<T> src, Copyable.Context context)
/*  95:    */       {
/*  96:137 */         return (List)Util.copy(src, Util.this, context);
/*  97:    */       }
/*  98:    */     };
/*  99:    */   }
/* 100:    */   
/* 101:    */   public static <T, CT extends Collection<T>> CT copy(CT src, Copyable.Copier<T> elemeCopier, Copyable.Context context)
/* 102:    */   {
/* 103:154 */     Collection<?> realCollectionSrc = src;
/* 104:156 */     while ((realCollectionSrc instanceof CollectionWrapper)) {
/* 105:157 */       realCollectionSrc = ((CollectionWrapper)src).delegate();
/* 106:    */     }
/* 107:159 */     Class<?> c = realCollectionSrc.getClass();
/* 108:    */     try
/* 109:    */     {
/* 110:162 */       CT ret = (Collection)c.newInstance();
/* 111:163 */       for (T elt : src) {
/* 112:164 */         ret.add(elemeCopier.copy(elt, context));
/* 113:    */       }
/* 114:165 */       return ret;
/* 115:    */     }
/* 116:    */     catch (SecurityException|InstantiationException|IllegalAccessException|IllegalArgumentException e)
/* 117:    */     {
/* 118:173 */       throw new IllegalArgumentException("Cannot deeply copy this collection:the class is impossible to construct with 0 argumentand is not an instance of CollectionWrapper (" + 
/* 119:    */       
/* 120:175 */         c + ")");
/* 121:    */     }
/* 122:    */   }
/* 123:    */   
/* 124:    */   public static <T, CT extends Collection<T>> CT copy(CT src, Copyable.Copier<T> elemeCopier)
/* 125:    */   {
/* 126:182 */     return copy(src, elemeCopier, getContext());
/* 127:    */   }
/* 128:    */   
/* 129:    */   public static <T extends Copyable, CT extends Collection<T>> CT copy(CT src, Copyable.Context context)
/* 130:    */   {
/* 131:189 */     copy(src, new Copyable.Copier()
/* 132:    */     {
/* 133:    */       public T copy(T src, Copyable.Context context)
/* 134:    */       {
/* 135:192 */         return Util.copy(src, context);
/* 136:    */       }
/* 137:194 */     }, context);
/* 138:    */   }
/* 139:    */   
/* 140:    */   public static <T extends Copyable, CT extends Collection<T>> CT copy(CT src)
/* 141:    */   {
/* 142:200 */     return copy(src, getContext());
/* 143:    */   }
/* 144:    */   
/* 145:    */   public static <T, CT extends Collection<T>> CT shallowCopy(CT src)
/* 146:    */   {
/* 147:    */     try
/* 148:    */     {
/* 149:217 */       return (Collection)src.getClass().getDeclaredMethod("clone", new Class[0]).invoke(src, new Object[0]);
/* 150:    */     }
/* 151:    */     catch (NoSuchMethodException|IllegalAccessException|IllegalArgumentException|InvocationTargetException e)
/* 152:    */     {
/* 153:221 */       Collection<?> realCollectionSrc = src;
/* 154:223 */       while ((realCollectionSrc instanceof CollectionWrapper)) {
/* 155:224 */         realCollectionSrc = ((CollectionWrapper)src).delegate();
/* 156:    */       }
/* 157:226 */       Class<?> c = realCollectionSrc.getClass();
/* 158:    */       try
/* 159:    */       {
/* 160:229 */         CT ret = (Collection)c.newInstance();
/* 161:230 */         ret.addAll(src);
/* 162:231 */         return ret;
/* 163:    */       }
/* 164:    */       catch (SecurityException|InstantiationException|IllegalAccessException|IllegalArgumentException f)
/* 165:    */       {
/* 166:239 */         throw new Error(
/* 167:240 */           "Cannot shallowCopy this collection: the class has no public clone methodand is impossible to construct with 0 argument");
/* 168:    */       }
/* 169:    */     }
/* 170:    */   }
/* 171:    */   
/* 172:    */   public static <T extends Viewable<V>, V extends Viewable.View> Converter<List<T>, ListView<V>> getListViewer()
/* 173:    */   {
/* 174:261 */     new Converter()
/* 175:    */     {
/* 176:    */       public ListView<V> convert(List<T> src)
/* 177:    */       {
/* 178:264 */         return Util.view(src);
/* 179:    */       }
/* 180:    */     };
/* 181:    */   }
/* 182:    */   
/* 183:    */   public static <T extends Viewable<V>, V extends Viewable.View> Converter<Collection<T>, CollectionView<V>> getCollectionViewer()
/* 184:    */   {
/* 185:273 */     new Converter()
/* 186:    */     {
/* 187:    */       public CollectionView<V> convert(Collection<T> src)
/* 188:    */       {
/* 189:276 */         return Util.view(src);
/* 190:    */       }
/* 191:    */     };
/* 192:    */   }
/* 193:    */   
/* 194:    */   public static <T extends Viewable<V>, V extends Viewable.View> Converter<List<T>, ListView<V>> getViewer(List<T> src)
/* 195:    */   {
/* 196:286 */     return getListViewer();
/* 197:    */   }
/* 198:    */   
/* 199:    */   public static <T extends Viewable<V>, V extends Viewable.View> Converter<Collection<T>, CollectionView<V>> getViewer(Collection<T> src)
/* 200:    */   {
/* 201:293 */     return getCollectionViewer();
/* 202:    */   }
/* 203:    */   
/* 204:    */   public static <T extends Viewable<V>, V extends Viewable.View> Converter<T, V> getViewer()
/* 205:    */   {
/* 206:300 */     new Converter()
/* 207:    */     {
/* 208:    */       public V convert(T src)
/* 209:    */       {
/* 210:302 */         return src.view();
/* 211:    */       }
/* 212:    */     };
/* 213:    */   }
/* 214:    */   
/* 215:    */   public static <T extends Viewable<V>, V extends Viewable.View> Converter<T, V> getViewer(Dummy<T> arg)
/* 216:    */   {
/* 217:311 */     new Converter()
/* 218:    */     {
/* 219:    */       public V convert(T src)
/* 220:    */       {
/* 221:313 */         return src.view();
/* 222:    */       }
/* 223:    */     };
/* 224:    */   }
/* 225:    */   
/* 226:    */   public static <T extends Viewable<V>, V extends Viewable.View> Converter<T, V> getViewer(T src)
/* 227:    */   {
/* 228:325 */     new Converter()
/* 229:    */     {
/* 230:    */       public V convert(T src)
/* 231:    */       {
/* 232:327 */         return src.view();
/* 233:    */       }
/* 234:    */     };
/* 235:    */   }
/* 236:    */   
/* 237:    */   public static <T extends Viewable<V>, V extends Viewable.View> Converter<Unique<T>, V> getViewer(Unique<T> src)
/* 238:    */   {
/* 239:336 */     new Converter()
/* 240:    */     {
/* 241:    */       public V convert(Unique<T> src)
/* 242:    */       {
/* 243:338 */         return Util.view(src);
/* 244:    */       }
/* 245:    */     };
/* 246:    */   }
/* 247:    */   
/* 248:    */   public static <V extends Viewable.View, T extends Viewable<V>> CollectionView<V> view(Collection<T> src)
/* 249:    */   {
/* 250:360 */     return new CollectionView.Of(src);
/* 251:    */   }
/* 252:    */   
/* 253:    */   public static <V extends Viewable.View, T extends Viewable<V>> SetView<V> view(Set<T> src)
/* 254:    */   {
/* 255:367 */     return new SetView.Of(src);
/* 256:    */   }
/* 257:    */   
/* 258:    */   public static <K, V extends Viewable.View, T extends Viewable<V>> MapView<K, V> view(Map<K, T> src)
/* 259:    */   {
/* 260:374 */     return new MapView.Of(src);
/* 261:    */   }
/* 262:    */   
/* 263:    */   public static <V extends Viewable.View, T extends Viewable<V>> ListView<V> view(List<T> src)
/* 264:    */   {
/* 265:381 */     return new ListView.Of(src);
/* 266:    */   }
/* 267:    */   
/* 268:    */   public static <V extends Viewable.View, T extends Viewable<V>> V view(Unique<T> src)
/* 269:    */   {
/* 270:388 */     return Unique.view(src);
/* 271:    */   }
/* 272:    */   
/* 273:    */   public static <V extends Viewable.View, T extends Viewable<V>> V view(T src)
/* 274:    */   {
/* 275:395 */     return src.view();
/* 276:    */   }
/* 277:    */   
/* 278:    */   public static <T> CollectionView<T> shallowView(Collection<T> src)
/* 279:    */   {
/* 280:403 */     return new CollectionView.ShallowOf(src);
/* 281:    */   }
/* 282:    */   
/* 283:    */   public static <T> SetView<T> shallowView(Set<T> src)
/* 284:    */   {
/* 285:410 */     return new SetView.ShallowOf(src);
/* 286:    */   }
/* 287:    */   
/* 288:    */   public static <T> ListView<T> shallowView(List<T> src)
/* 289:    */   {
/* 290:417 */     return new ListView.ShallowOf(src);
/* 291:    */   }
/* 292:    */   
/* 293:    */   public static <T, U> CollectionView<U> transform(Collection<T> src, Converter<T, U> eltTransformer)
/* 294:    */   {
/* 295:425 */     return new CollectionView.Transform(src, eltTransformer);
/* 296:    */   }
/* 297:    */   
/* 298:    */   public static <T, U> ListView<U> transformView(List<T> src, Converter<T, U> eltTransformer)
/* 299:    */   {
/* 300:431 */     return new ListView.Transform(src, eltTransformer);
/* 301:    */   }
/* 302:    */   
/* 303:    */   public static abstract interface ConditionalConverter<T, U>
/* 304:    */     extends Util.Converter<T, U>
/* 305:    */   {
/* 306:    */     public abstract boolean canConvert(T paramT);
/* 307:    */   }
/* 308:    */   
/* 309:    */   public static abstract interface Converter<T, U>
/* 310:    */   {
/* 311:    */     public abstract U convert(T paramT);
/* 312:    */   }
/* 313:    */   
/* 314:    */   public static final class Dummy<T> {}
/* 315:    */   
/* 316:    */   public static abstract interface Predicate<T>
/* 317:    */     extends Util.Converter<T, Boolean>
/* 318:    */   {}
/* 319:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.Util
 * JD-Core Version:    0.7.0.1
 */