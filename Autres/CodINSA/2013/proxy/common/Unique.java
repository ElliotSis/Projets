/*   1:    */ package common;
/*   2:    */ 
/*   3:    */ import java.util.Collection;
/*   4:    */ 
/*   5:    */ public class Unique<T>
/*   6:    */ {
/*   7:    */   protected T object;
/*   8:    */   
/*   9:    */   protected Unique(T object)
/*  10:    */   {
/*  11: 25 */     this.object = object;
/*  12:    */   }
/*  13:    */   
/*  14:    */   public final T take()
/*  15:    */   {
/*  16: 28 */     if (this.object != null)
/*  17:    */     {
/*  18: 29 */       T ret = this.object;
/*  19: 30 */       this.object = null;
/*  20: 31 */       return ret;
/*  21:    */     }
/*  22: 33 */     throw new ExpiredCopyException();
/*  23:    */   }
/*  24:    */   
/*  25:    */   public final boolean taken()
/*  26:    */   {
/*  27: 36 */     return this.object == null;
/*  28:    */   }
/*  29:    */   
/*  30:    */   public static <V extends Viewable.View, T extends Viewable<V>> V view(Unique<T> src)
/*  31:    */   {
/*  32: 44 */     if (src.object == null) {
/*  33: 45 */       throw new ExpiredCopyException();
/*  34:    */     }
/*  35: 46 */     return ((Viewable)src.object).view();
/*  36:    */   }
/*  37:    */   
/*  38:    */   public static class ExpiredCopyException
/*  39:    */     extends RuntimeException
/*  40:    */   {
/*  41:    */     private static final long serialVersionUID = 1L;
/*  42:    */     
/*  43:    */     public ExpiredCopyException()
/*  44:    */     {
/*  45: 52 */       super();
/*  46:    */     }
/*  47:    */   }
/*  48:    */   
/*  49:    */   public static class Copy<T>
/*  50:    */     extends Unique<T>
/*  51:    */   {
/*  52:    */     public Copy(T original, Copyable.Copier<T> copier)
/*  53:    */     {
/*  54: 63 */       super();
/*  55:    */     }
/*  56:    */     
/*  57:    */     public Copy(T original, Copyable.Copier<T> copier, Copyable.Context context)
/*  58:    */     {
/*  59: 67 */       super();
/*  60:    */     }
/*  61:    */     
/*  62:    */     public static <T extends Copyable> Copy<T> make(T src)
/*  63:    */     {
/*  64: 82 */       return new Copy(Util.copy(src));
/*  65:    */     }
/*  66:    */     
/*  67:    */     public static <T extends Copyable> Copy<T> make(T src, Copyable.Context context)
/*  68:    */     {
/*  69: 85 */       return new Copy(Util.copy(src, context));
/*  70:    */     }
/*  71:    */     
/*  72:    */     private Copy(T copy)
/*  73:    */     {
/*  74: 89 */       super();
/*  75:    */     }
/*  76:    */   }
/*  77:    */   
/*  78:    */   public static class Collection<T, CT extends Collection<T>>
/*  79:    */     extends Unique<CT>
/*  80:    */   {
/*  81:    */     public Collection(Class<?> c)
/*  82:    */     {
/*  83:113 */       super();
/*  84:    */     }
/*  85:    */     
/*  86:    */     static <CT> CT helper(Class<CT> c)
/*  87:    */     {
/*  88:    */       try
/*  89:    */       {
/*  90:118 */         return c.newInstance();
/*  91:    */       }
/*  92:    */       catch (InstantiationException|IllegalAccessException e)
/*  93:    */       {
/*  94:120 */         throw new IllegalArgumentException("The collection class passed to Unique.Collectionmust be instantiable with no argument (" + 
/*  95:121 */           c + ")", e);
/*  96:    */       }
/*  97:    */     }
/*  98:    */     
/*  99:    */     public boolean add(Unique<T> elt)
/* 100:    */     {
/* 101:126 */       return ((Collection)this.object).add(elt.take());
/* 102:    */     }
/* 103:    */   }
/* 104:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.Unique
 * JD-Core Version:    0.7.0.1
 */