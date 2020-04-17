
#define offset_of(type, member) ((char *)&(((type *)0)->member))

#define container_of(ptr, type, member) ({ \
    const typeof(((type *)0)->member) *m_ptr = ptr; \
    (type *)((char *)m_ptr - offset_of(type, member));})


class CAA
{
public:
    CAA() : a(0) {}

    int a;
};

void TESTContainer()
{
//    B *b = container_of(this, B, ca);

//    qDebug() << b->b;
}
