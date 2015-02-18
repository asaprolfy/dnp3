#ifndef DNP3_APP_H_SEEN
#define DNP3_APP_H_SEEN


void dnp3_p_init_app(void);

// short-hands to save some noise in group/variation arguments
#define G(g)     DNP3_GROUP_##g
#define V(g,v)   DNP3_VARIATION_##g##_##v
#define G_V(g,v) G(g),V(g,v)
#define GV(g,v)  (G(g) << 8 | V(g,v))

// parse an "rblock" for the given group/variations, that is a block of object
// headers and possibly object prefixes, as used in read requests.
// allows variation 0 ("any").
// the value 0 is also used to terminate the argument list.
HParser *dnp3_p_rblock(DNP3_Group g, ...);

// parse an "rblock" for exactly the given group/variation.
HParser *dnp3_p_specific_rblock(DNP3_Group g, DNP3_Variation v);

// parse an "rblock" for all objects (qc=06) of the given group/variation.
HParser *dnp3_p_rblock_all(DNP3_Group g, DNP3_Variation v);

// parse an "rblock" for all or a maximum number of objects (qc=06-08)
HParser *dnp3_p_rblock_max(DNP3_Group g, DNP3_Variation v);

// parse an "oblock" of a single object of the given type.
HParser *dnp3_p_single(DNP3_Group g, DNP3_Variation v, HParser *obj);

// parse an "rblock" for a single object of the given type.
HParser *dnp3_p_single_rblock(DNP3_Group g, DNP3_Variation v);

// parse an "oblock" of a single variable-format object of the given type.
HParser *dnp3_p_single_vf(DNP3_Group g, DNP3_Variation v, HParser *(*obj)(size_t));

// parse an "oblock" of objects of the given type.
HParser *dnp3_p_oblock(DNP3_Group g, DNP3_Variation v, HParser *obj);

// like dnp3_p_oblock but only accept range formats, parse objects little-endian,
// and pad with zero bits up to the next byte boundary
HParser *dnp3_p_oblock_packed(DNP3_Group g, DNP3_Variation v, HParser *obj);

// parse an "oblock" of variable-format objects of the given type.
HParser *dnp3_p_oblock_vf(DNP3_Group g, DNP3_Variation v, HParser *(*obj)(size_t));



#endif  // DNP3_APP_H_SEEN
