/* SPDX-License-Identifier: GPL-3.0-only
 * Pattern generator adapted for Skiffplus.
 *
 * Include from ui_tools.c after tl_undo_take() is defined.
 * Generates a four-bar / 64-step pattern on each track.
 * The generator chooses its own ROOT and SCALE.
 * Engines stay unchanged; compatible presets are chosen within each engine.
 */

enum { DICE_DRUM, DICE_BASS, DICE_PAD, DICE_LEAD, DICE_ARP, DICE_TEX, DICE_ROLE_N };
enum {
    DICE_MOTORIK, DICE_ELECTRO, DICE_BREAK, DICE_BROKEN,
    DICE_MINIMAL, DICE_DEEP, DICE_HARD, DICE_PUNK, DICE_INDIE,
    DICE_SPARSE, DICE_IDM, DICE_FUNK, DICE_NO_DRUM
};
enum {
    DICE_KIT_808, DICE_KIT_HARD, DICE_KIT_CLICK, DICE_KIT_INDUS,
    DICE_KIT_SOFT, DICE_KIT_GLITCH, DICE_KIT_ELECTRO, DICE_KIT_BREAKS
};
enum { DICE_BASS_OCT8, DICE_BASS_PUMP, DICE_BASS_ACID, DICE_BASS_DRONE,
       DICE_BASS_ROLL, DICE_BASS_BLIP, DICE_BASS_SUB, DICE_BASS_PUNK,
       DICE_BASS_INDIE, DICE_BASS_RUMBLE, DICE_BASS_IDM, DICE_BASS_FIFTHS, DICE_BASS_WALK };
enum { DICE_PAD_HOLD, DICE_PAD_STAB, DICE_PAD_PULSE, DICE_PAD_SPARSE,
       DICE_PAD_DUB, DICE_PAD_SWELL,DICE_PAD_COMP };
enum { DICE_VC_7, DICE_VC_9, DICE_VC_QUART, DICE_VC_SUS,
       DICE_VC_ADD9, DICE_VC_MIX };
enum { DICE_LEAD_MOTIF, DICE_LEAD_OSTINATO, DICE_LEAD_SPARSE, DICE_LEAD_TINTI };
enum { DICE_ARP_UPDOWN, DICE_ARP_ALBERTI, DICE_ARP_GLASS,
       DICE_ARP_PULSE, DICE_ARP_WALK };

/* Local scale IDs: these are not the track's P_SCALE values. */
enum { DICE_SC_MAJ, DICE_SC_MIN, DICE_SC_DOR, DICE_SC_MIX,
       DICE_SC_PEN, DICE_SC_MPEN, DICE_SC_HARM, DICE_SC_PHRY,
       DICE_SC_LYD, DICE_SC_MEL, DICE_SC_BLUES };

#define DICE_X 127

typedef struct {
    const char *name;
    uint8_t scale[4];
    int8_t prog[3][4];
    uint8_t drums, drum_pct, kit[2];
    uint8_t bass, pads, voicing, lead, arp;
    uint8_t energy_lo, energy_hi;
    uint8_t prio[5];
    uint8_t odd, bars;
} dice_style_t;

#define DICE_PRIO_DANCE {DICE_BASS, DICE_PAD, DICE_LEAD, DICE_ARP, DICE_TEX}
#define DICE_PRIO_ARP   {DICE_BASS, DICE_ARP, DICE_PAD, DICE_LEAD, DICE_TEX}
#define DICE_PRIO_PADS  {DICE_PAD, DICE_TEX, DICE_LEAD, DICE_BASS, DICE_ARP}
#define DICE_PRIO_SONG  {DICE_BASS, DICE_LEAD, DICE_PAD, DICE_ARP, DICE_TEX}
#define DICE_PRIO_CLASS {DICE_ARP, DICE_PAD, DICE_LEAD, DICE_TEX, DICE_BASS}

/* Retained composition parameters from the supplied DSTYLE/gen tables.
 * Tempo, global effects, and unrelated genres are deliberately omitted. */
static const dice_style_t DICE_STYLES[] = {
    {"IDM", {DICE_SC_PHRY, DICE_SC_HARM, DICE_SC_MIN, DICE_SC_DOR},
     {{0, 5, 1, DICE_X}, {0, 3, 1, 5}, {0, 1, 5, 4}},
     DICE_IDM, 85, {DICE_KIT_GLITCH, DICE_KIT_CLICK},
     DICE_BASS_IDM, DICE_PAD_SPARSE, DICE_VC_MIX, DICE_LEAD_MOTIF, DICE_ARP_WALK,
     0, 2, DICE_PRIO_ARP, 60, 1},

    {"BROKEN", {DICE_SC_DOR, DICE_SC_MIN, DICE_SC_MEL, DICE_SC_DOR},
     {{0, 3, DICE_X, DICE_X}, {0, DICE_X, DICE_X, DICE_X}, {0, 6, 3, DICE_X}},
     DICE_BROKEN, 70, {DICE_KIT_SOFT, DICE_KIT_GLITCH},
     DICE_BASS_DRONE, DICE_PAD_SPARSE, DICE_VC_QUART, DICE_LEAD_MOTIF, DICE_ARP_WALK,
     0, 1, DICE_PRIO_SONG, 60, 2},

    {"AMBIENT", {DICE_SC_PEN, DICE_SC_PEN, DICE_SC_PEN, DICE_SC_MAJ},
     {{0, 4, 2, 5}, {0, 2, 4, DICE_X}, {0, 5, 3, 4}},
     DICE_SPARSE, 18, {DICE_KIT_SOFT, DICE_KIT_CLICK},
     DICE_BASS_DRONE, DICE_PAD_SWELL, DICE_VC_ADD9, DICE_LEAD_SPARSE, DICE_ARP_GLASS,
     0, 1, DICE_PRIO_PADS, 45, 2},

    {"IMPRESSION", {DICE_SC_LYD, DICE_SC_MAJ, DICE_SC_LYD, DICE_SC_PEN},
     {{0, 1, 3, 4}, {0, 2, 4, DICE_X}, {0, 5, 3, 4}},
     DICE_SPARSE, 20, {DICE_KIT_SOFT, DICE_KIT_CLICK},
     DICE_BASS_FIFTHS, DICE_PAD_SWELL, DICE_VC_QUART, DICE_LEAD_TINTI, DICE_ARP_UPDOWN,
     0, 1, DICE_PRIO_PADS, 35, 2},

    {"FUNK", {DICE_SC_DOR, DICE_SC_MIX, DICE_SC_MPEN, DICE_SC_BLUES},
     {{0, 3, 0, 4}, {0, 5, 3, 4}, {0, 3, 5, 0}},
     DICE_FUNK, 90, {DICE_KIT_BREAKS, DICE_KIT_SOFT},
     DICE_BASS_WALK, DICE_PAD_COMP, DICE_VC_9, DICE_LEAD_MOTIF, DICE_ARP_WALK,
     1, 2, DICE_PRIO_DANCE, 20, 1},
};
//#define DICE_NSTYLE (sizeof DICE_STYLES / sizeof DICE_STYLES[0])
#define DICE_NSTYLE 5

/* The genre-specific pentatonic and chord voicings. */
static const uint16_t DICE_SCALE_MASK[11] = {
    [DICE_SC_MAJ]   = (1u << 0) | (1u << 2) | (1u << 4) | (1u << 5) |
                      (1u << 7) | (1u << 9) | (1u << 11),
    [DICE_SC_MIN]   = (1u << 0) | (1u << 2) | (1u << 3) | (1u << 5) |
                      (1u << 7) | (1u << 8) | (1u << 10),
    [DICE_SC_DOR]   = (1u << 0) | (1u << 2) | (1u << 3) | (1u << 5) |
                      (1u << 7) | (1u << 9) | (1u << 10),
    [DICE_SC_MIX]   = (1u << 0) | (1u << 2) | (1u << 4) | (1u << 5) |
                      (1u << 7) | (1u << 9) | (1u << 10),
    [DICE_SC_PEN]   = (1u << 0) | (1u << 2) | (1u << 4) |
                      (1u << 7) | (1u << 9),
    [DICE_SC_MPEN]  = (1u << 0) | (1u << 3) | (1u << 5) |
                      (1u << 7) | (1u << 10),
    [DICE_SC_HARM]  = (1u << 0) | (1u << 2) | (1u << 3) | (1u << 5) |
                      (1u << 7) | (1u << 8) | (1u << 11),
    [DICE_SC_PHRY]  = (1u << 0) | (1u << 1) | (1u << 3) | (1u << 5) |
                      (1u << 7) | (1u << 8) | (1u << 10),
    [DICE_SC_LYD]   = (1u << 0) | (1u << 2) | (1u << 4) | (1u << 6) |
                      (1u << 7) | (1u << 9) | (1u << 11),
    [DICE_SC_MEL]   = (1u << 0) | (1u << 2) | (1u << 3) | (1u << 5) |
                      (1u << 7) | (1u << 9) | (1u << 11),
    [DICE_SC_BLUES] = (1u << 0) | (1u << 3) | (1u << 5) |
                      (1u << 6) | (1u << 7) | (1u << 10),
};

static struct {
    const dice_style_t *style;
    uint32_t progression;
    uint32_t chord_steps;
    uint32_t progression_n;
    uint32_t energy;
    uint32_t scale;
    uint32_t root;
    int32_t last[4];
    uint32_t last_n;
} dice_piece;

static int32_t dice_rr(int32_t lo, int32_t hi)
{
    return lo + (int32_t)(rng() % (uint32_t)(hi - lo + 1));
}
static int dice_chance(uint32_t pct) { return rng() % 100u < pct; }

static int32_t dice_note(const track_t *t, int32_t lo, int32_t degree)
{
    uint32_t mask = DICE_SCALE_MASK[dice_piece.scale];
    int32_t root = (int32_t)dice_piece.root;
    int32_t note = lo + ((root - lo) % 12 + 12) % 12;
    int32_t dir = degree < 0 ? -1 : 1;
    uint32_t left = (uint32_t)(degree < 0 ? -degree : degree);
    uint32_t guard = 0;

    (void)t;
    while (left && guard++ < 128u) {
        note += dir;
        if (note < 0 || note > 127)
            break;
        if ((mask >> (uint32_t)((note - root + 120) % 12)) & 1u)
            left--;
    }
    return clamp(note, 0, 127);
}
#undef DICE_X

static uint32_t dice_chord_at(uint32_t step)
{
    const int8_t *p = dice_piece.style->prog[dice_piece.progression];
    return (uint32_t)p[(step / dice_piece.chord_steps) % dice_piece.progression_n];
}

static void dice_step_note(step_t *s, const int32_t *notes, uint32_t count,
                           uint32_t vel, uint32_t flags)
{
    step_clear(s);
    s->time = ST_NOTE;
    s->n = (uint8_t)(count > 4u ? 4u : count);
    s->vel = (uint8_t)clamp((int32_t)vel, 1, 127);
    s->flags = (uint8_t)flags;
    for (uint32_t k = 0; k < s->n; k++)
        s->note[k] = (uint8_t)clamp(notes[k], 0, 127);
}

static void dice_hold(track_t *t, uint32_t at, uint32_t n, uint32_t len)
{
    for (uint32_t j = 1; j <= n && at + j < len; j++) {
        step_t *s = &t->step[at + j];
        if (s->time == ST_NOTE && (s->n || s->hit))
            break;
        step_clear(s);
        s->time = ST_TIE;
    }
}

static int dice_euclid(uint32_t i, uint32_t hits, uint32_t n, uint32_t rot)
{
    if (!n || !hits)
        return 0;
    i = (i + rot) % n;
    return (i * hits) % n < hits;
}

static const char *const DICE_DRUM_BAR[][8] = {
    [DICE_MINIMAL] = {"a...x...a...x...", "", "....g.......g...", "g.x...xgg.x...x.",
                      "..x...x...x...x.", "", "...x..g...x..x..", "......g........."},
    [DICE_DEEP]    = {"a...x...a...x...", "", "............g...", "..x...x...x...x.",
                      "..g...x...g...x.", "", ".g.....x.g....x.", ""},
    [DICE_BROKEN]  = {"x..x....x.x.....", "....a..g.g..a...", "",
                      "x.xgx.x.x.xgx.x.", ".......x........", "", "", ""},
    [DICE_SPARSE]  = {"x...............", "", "", "", "", "", "......g.....x...", "..........g....."},
    [DICE_FUNK]    = {"a..x..x.a.x.....", "...g.x..g...x..g", "", "x.x.x.x.x.x.x.x.",
                      "..............x.", "", "..x.....x.......", ""},
};

static void dice_drums(track_t *t, uint32_t len)
{
    const dice_style_t *st = dice_piece.style;
    uint32_t e = dice_piece.energy;

    if (st->drums == DICE_NO_DRUM)
        return;

    if (st->drums == DICE_IDM) {
        uint32_t kb = (uint32_t)dice_rr(3, 6);
        uint32_t ks = (uint32_t)dice_rr(2, 4);
        uint32_t kh = (uint32_t)dice_rr(5, 9) + e * 2u;
        uint32_t rot = (uint32_t)dice_rr(0, 7);

        for (uint32_t i = 0; i < len; i++) {
            uint32_t h = 0;
            uint32_t bar = i / 16u;

            if (dice_euclid(i, kb, 16u, rot + (bar == 3u ? 2u : 0u))
                ) h |= 1u << DV_KICK;
            if (dice_euclid(i, ks, 16u, rot + 4u) && !(h & (1u << DV_KICK)))
                h |= 1u << (dice_chance(50) ? DV_SNARE : DV_RIM);
            if (dice_euclid(i, kh + (bar & 1u) * 2u, 16u, bar) &&
                (e || dice_chance(40)))
                h |= 1u << (dice_chance(20) ? DV_HATO : DV_HATC);
            if (dice_chance(8))
                h |= 1u << (DV_TOM + rng() % 3u);

            if (h) {
                t->step[i].time = ST_NOTE;
                t->step[i].hit = (uint8_t)h;
                t->step[i].vel = (uint8_t)((h & (1u << DV_KICK)) ? 104u : dice_rr(70, 96));
                if ((h & (1u << DV_HATC)) && dice_chance(e == 2u ? 40u : 15u))
                    step_set_ratchet(&t->step[i], (uint32_t)dice_rr(2, 4));
                if (!(h & (1u << DV_KICK)) && dice_chance(30))
                    step_set_chance(&t->step[i], (uint32_t)dice_rr(45, 85));
            }
        }
        return;
    }

    for (uint32_t i = 0; i < len; i++) {
        uint32_t h = 0, acc = 0;
        uint32_t p = i % 16u;
        uint32_t fill = len > 16u && i >= len - 4u &&
                        st->drums != DICE_DEEP && st->drums != DICE_SPARSE && e;

        for (uint32_t lane = 0; lane < NLANE; lane++) {
            const char *bar = DICE_DRUM_BAR[st->drums][lane];
            char c = bar && bar[0] ? bar[p] : '.';

            if (c == 'x' || c == 'a' || (c == 'g' && rng() % 4u))
                h |= 1u << lane;
            if (c == 'a')
                acc |= 1u << lane;
        }

        if (e == 0u && (h & 0x18u) && dice_chance(65))
            h &= ~0x18u;
        if (e == 2u && !(h & 0x18u) && p % 2u == 1u && dice_chance(35))
            h |= 1u << DV_HATC;
        if (fill) {
            if (dice_chance(50))
                h |= 1u << (dice_chance(50) ? DV_SNARE : DV_TOM);
            h &= ~(1u << DV_HATO);
        }
        if (i >= 16u && !fill && dice_chance(8))
            h ^= 1u << (dice_chance(50) ? DV_RIM : DV_BELL);

        if (!h)
            continue;
        t->step[i].time = ST_NOTE;
        t->step[i].hit = (uint8_t)h;
        t->step[i].acc = (uint8_t)acc;
        t->step[i].vel = (uint8_t)(acc ? 104u : dice_rr(82, 108));
        if (fill && dice_chance(40))
            step_set_ratchet(&t->step[i], 2u);
        if ((h & (1u << DV_HATC)) && dice_chance(e == 2u ? 14u : 4u))
            step_set_ratchet(&t->step[i], 2u);
    }
}

static void dice_bass(track_t *t, uint32_t len)
{
    const dice_style_t *st = dice_piece.style;
    uint32_t e = dice_piece.energy;
    static const uint8_t PUMP[16] = {1, 0, 0, 1, 0, 0, 1, 0,
                                     0, 0, 1, 1, 0, 0, 1, 0};
    uint8_t acid[16], roll[16], indie[16];
    int32_t base = 28;

    for (uint32_t i = 0; i < 16u; i++) {
        acid[i] = (uint8_t)(i % 4u == 0u ? 1u :
                   dice_chance(30u + e * 10u) ? 1u + rng() % 4u : 0u);
        roll[i] = (uint8_t)(i % 4u == 2u ? 1u :
                   i % 4u == 3u ? dice_chance(20u + e * 15u) :
                   i % 4u == 1u ? dice_chance(e * 8u) : 0u);
        indie[i] = (uint8_t)(i == 0u || i == 10u ||
                    (i == 6u && dice_chance(50)) ||
                    (i == 14u && dice_chance(40)));
    }

    if (st->bass != DICE_BASS_DRONE && st->bass != DICE_BASS_SUB && base < 33)
        base += 12;

    for (uint32_t i = 0; i < len; i++) {
        step_t *s = &t->step[i];
        uint32_t p = i % 16u;
        int32_t d = (int32_t)dice_chord_at(i), delta = 0;
        uint32_t on = 0, octave = 0, hold = 0;
        uint32_t vel = 96u, flags = 0;

        switch (st->bass) {
        case DICE_BASS_FIFTHS:
            on = p == 0u || p == 8u;
            delta = p == 8u ? 4 : 0; /* fondamentale puis quinte */
            hold = p == 0u ? 5u : 3u;
            break;

        case DICE_BASS_WALK: 
            // static const int8_t WALK[8] = {0, 2, 4, 2, 0, 2, 4, 6};
            on = p % 2u == 0u;
            // delta = WALK[(p / 2u) % 8u];
            delta = 0;
            vel = p % 4u == 0u ? 96u : 78u;
            break;            
        case DICE_BASS_OCT8:
            on = i % 2u == 0u && (e || i % 4u == 0u);
            octave = (i / 2u) & 1u;
            break;
        case DICE_BASS_PUMP:
            on = PUMP[p];
            octave = p == 11u;
            flags = p == 0u ? SF_ACCENT : 0u;
            break;
        case DICE_BASS_ACID:
            on = acid[p] != 0u;
            delta = acid[p] == 2u ? 1 : acid[p] == 3u ? 4 :
                    acid[p] == 4u ? -1 : 0;
            octave = acid[p] == 3u && dice_chance(50);
            flags = p % 4u == 0u ? SF_ACCENT : 0u;
            if (dice_chance(25))
                flags |= SF_SLIDE;
            break;
        case DICE_BASS_DRONE:
            on = i % (dice_piece.chord_steps < 16u ? dice_piece.chord_steps : 16u) == 0u;
            hold = 15u;
            break;
        case DICE_BASS_ROLL:
            on = roll[p];
            vel = p % 4u == 2u ? 100u : 80u;
            break;
        case DICE_BASS_SUB:
            on = p == 0u || (e && p == 10u) || (e == 2u && p == 6u);
            hold = p == 0u ? (e ? 5u : 13u) : 2u;
            if (p == 10u && dice_chance(40))
                delta = 4;
            break;
        case DICE_BASS_BLIP:
            on = (p % 4u == 2u && dice_chance(70)) || p == 0u;
            vel = 90u;
            break;
        case DICE_BASS_PUNK:
            on = i % 2u == 0u;
            if (p >= 12u && dice_chance(40))
                delta = 4;
            flags = p % 8u == 0u ? SF_ACCENT : 0u;
            break;
        case DICE_BASS_INDIE:
            on = indie[p];
            if (p == 14u)
                delta = (int32_t)dice_chord_at(i + 2u) - d - 1;
            else if (p == 10u && dice_chance(40))
                delta = 4;
            hold = p == 0u ? 3u : 1u;
            break;
        case DICE_BASS_RUMBLE:
            on = p % 4u != 0u &&
                 (p % 4u == 2u || dice_chance(30u + e * 20u));
            vel = p % 4u == 2u ? 96u : 76u;
            break;
        default: /* IDM */
            on = dice_chance(25u + e * 10u);
            delta = (int32_t)(rng() % 3u) * 2 - 2;
            octave = dice_chance(10);
            break;
        }

        if (!on)
            continue;

        {
            int32_t note = dice_note(t, base + (octave ? 12 : 0), d + delta);
            dice_step_note(s, &note, 1u,
                           vel + ((flags & SF_ACCENT) ? 16u : 0u), flags);
        }
        if (hold)
            dice_hold(t, i, hold, len);
        if (st->bass == DICE_BASS_IDM && dice_chance(12))
            step_set_ratchet(s, 2u);
    }
}

static uint32_t dice_chord(track_t *t, int32_t lo, int32_t degree,
                           uint32_t voicing, int32_t *notes)
{
    static const int8_t V[5][4] = {
        {0, 2, 4, 6}, {0, 2, 6, 8}, {0, 3, 6, 9},
        {0, 3, 4, 8}, {0, 2, 4, 8}
    };
    int32_t tonic = dice_note(t, lo, 0);
    uint32_t k;

    if (voicing == DICE_VC_MIX)
        voicing = rng() % 5u;
    if (voicing > 4u)
        voicing = 0u;

    for (k = 0; k < 4u; k++) {
        notes[k] = dice_note(t, lo, degree + V[voicing][k]);
        while (notes[k] < tonic - 2)
            notes[k] += 12;
        while (notes[k] > tonic + 15)
            notes[k] -= 12;
    }

    if (dice_piece.last_n) {
        int32_t mid = 0;

        for (k = 0; k < dice_piece.last_n; k++)
            mid += dice_piece.last[k];
        mid /= (int32_t)dice_piece.last_n;

        for (k = 0; k < 4u; k++) {
            if (notes[k] - mid > 7 && notes[k] - 12 >= tonic - 5)
                notes[k] -= 12;
            else if (mid - notes[k] > 7 && notes[k] + 12 <= tonic + 17)
                notes[k] += 12;
        }
    }

    for (uint32_t i = 1; i < 4u; i++)
        for (k = i; k > 0u && notes[k] < notes[k - 1u]; k--) {
            int32_t tmp = notes[k];
            notes[k] = notes[k - 1u];
            notes[k - 1u] = tmp;
        }

    for (k = 1; k < 4u; k++)
        if (notes[k] == notes[k - 1u])
            notes[k] += 12;

    for (k = 0; k < 4u; k++)
        dice_piece.last[k] = notes[k];
    dice_piece.last_n = 4u;
    return 4u;
}

static void dice_pads(track_t *t, uint32_t len)
{
    const dice_style_t *st = dice_piece.style;
    int32_t tonic = 50, notes[4];
    uint32_t last_d = 0xFFFFFFFFu;
    uint8_t dub[16] = {0};
    static const uint8_t AT[6] = {6, 10, 14, 7, 11, 13};
    uint32_t m = (uint32_t)dice_rr(1, 2) + (dice_piece.energy == 2u);

    for (uint32_t j = 0; j < m; j++)
        dub[AT[rng() % 6u]] = 1u;
    dub[2] = 1u;
    dice_piece.last_n = 0;

    for (uint32_t i = 0; i < len; i++) {
        uint32_t pp = i % dice_piece.chord_steps;
        uint32_t p = i % 16u;
        uint32_t d = dice_chord_at(i);
        int on = 0;

        switch (st->pads) {
        case DICE_PAD_COMP:
            on = p == 2u || p == 6u || p == 10u || p == 14u ||
                 (pp == 0u && dice_chance(40));
            break;            
        case DICE_PAD_HOLD:
        case DICE_PAD_SWELL:
            on = pp == 0u;
            break;
        case DICE_PAD_STAB:
            on = (p % 4u == 2u &&
                  dice_chance(35u + dice_piece.energy * 15u)) ||
                 (pp == 0u && dice_chance(40));
            break;
        case DICE_PAD_PULSE:
            on = i % (dice_piece.energy == 2u ? 2u : 4u) == 0u &&
                 !(p == 12u && dice_chance(50));
            break;
        case DICE_PAD_DUB:
            on = dub[p];
            break;
        default:
            on = pp == 0u && (i == 0u || dice_chance(65));
            break;
        }

        if (!on)
            continue;

        if (d != last_d || st->pads == DICE_PAD_HOLD ||
            st->pads == DICE_PAD_SWELL || st->pads == DICE_PAD_SPARSE) {
            dice_chord(t, tonic, (int32_t)d, st->voicing, notes);
            last_d = d;
        } else {
            for (uint32_t k = 0; k < 4u; k++)
                notes[k] = dice_piece.last[k];
        }

        dice_step_note(&t->step[i], notes, 4u,
                       st->pads == DICE_PAD_DUB ? (p == 2u ? 90u : 78u) :
                       st->pads == DICE_PAD_COMP ? (p == 2u ? 84u : 76u) :
                       st->pads == DICE_PAD_SWELL ? 74u : 80u, 0u);

        if (st->pads == DICE_PAD_HOLD || st->pads == DICE_PAD_SWELL ||
            st->pads == DICE_PAD_SPARSE)
            dice_hold(t, i, dice_piece.chord_steps - 1u, len);
        else if (st->pads == DICE_PAD_PULSE && dice_chance(40))
            dice_hold(t, i, 1u, len);
    }
}

static int32_t dice_near_chord(int32_t degree, int32_t chord)
{
    int32_t best = chord;

    for (int32_t k = -7; k <= 11; k += 2) {
        int32_t c = chord + k;
        int32_t interval = ((c - chord) % 7 + 7) % 7;
        int32_t db = degree - best;
        int32_t dc = degree - c;

        if (interval != 0 && interval != 2 && interval != 4)
            continue;
        if ((dc < 0 ? -dc : dc) < (db < 0 ? -db : db))
            best = c;
    }
    return best;
}

static void dice_lead(track_t *t, uint32_t len)
{
    const dice_style_t *st = dice_piece.style;
    int32_t base = 55;

    if (st->lead == DICE_LEAD_OSTINATO) {
        static const int8_t CELL[6][4] = {
            {0, 0, 1, 0}, {0, 2, 1, 0}, {4, 2, 0, 1},
            {0, -1, 0, 2}, {0, 4, 3, 1}, {2, 1, 0, -2}
        };
        const int8_t *cell = CELL[rng() % 6u];
        uint32_t k = (uint32_t)dice_rr(3, 5) + dice_piece.energy;
        uint32_t rot = (uint32_t)dice_rr(0, 3);
        uint32_t nc = (uint32_t)dice_rr(2, 4);
        uint32_t j = 0;

        for (uint32_t i = 0; i < len; i++) {
            uint32_t bar = i / 16u;
            int32_t note;

            if (!dice_euclid(i % 16u, k, 16u, rot))
                continue;
            if (bar % 4u == 3u && dice_chance(50))
                continue;

            note = dice_note(t, base,
                             cell[j % nc] +
                             (bar % 4u == 2u && j % nc == nc - 1u ? 1 : 0));
            if (note > 79)
                note -= 12;
            dice_step_note(&t->step[i], &note, 1u,
                           j % nc == 0u ? 98u : 82u,
                           dice_chance(15) ? SF_SLIDE : 0u);
            j++;
        }
        return;
    }

    if (st->lead == DICE_LEAD_SPARSE || st->lead == DICE_LEAD_TINTI) {
        int32_t d = st->lead == DICE_LEAD_TINTI ? dice_rr(2, 5) : 2;
        int32_t dir = dice_chance(50) ? -1 : 1;

        for (uint32_t i = 0; i < len; i += 8u) {
            uint32_t bar = i / 16u;
            int32_t note;

            if (st->lead == DICE_LEAD_SPARSE &&
                ((i % 16u) || (bar % 2u == 1u && dice_chance(40))))
                continue;

            if (st->lead == DICE_LEAD_SPARSE) {
                d = dice_near_chord(d + dice_rr(-1, 1),
                                    (int32_t)dice_chord_at(i));
            } else {
                d += dir;
                if (d < -2 || d > 7) {
                    dir = -dir;
                    d += 2 * dir;
                }
            }

            note = dice_note(t, base, d);
            dice_step_note(&t->step[i], &note, 1u, 84u, 0u);
            dice_hold(t, i, st->lead == DICE_LEAD_TINTI ? 6u : 12u, len);
        }
        return;
    }

    {
        uint8_t at[6];
        int8_t degree[6];
        uint32_t k = (uint32_t)dice_rr(2, 3) + dice_piece.energy;
        uint32_t j = 0, rot = (uint32_t)dice_rr(0, 5);
        uint32_t bars = len / 16u ? len / 16u : 1u;
        int32_t d = (int32_t)(rng() % 3u) * 2;
        int32_t prev = 0;

        if (k > 5u)
            k = 5u;

        for (uint32_t i = 0; i < 16u && j < k; i++)
            if (dice_euclid(i, k, 16u, rot))
                at[j++] = (uint8_t)i;
        k = j;

        for (j = 0; j < k; j++) {
            int32_t move = dice_chance(70) ?
                           (dice_chance(50) ? 1 : -1) :
                           (dice_chance(50) ? dice_rr(2, 3) : -dice_rr(2, 3));

            if (j && (prev >= 2 || prev <= -2))
                move = prev > 0 ? -1 : 1;
            if (j)
                d = clamp(d + move, -3, 7);
            degree[j] = (int8_t)d;
            prev = j ? move : 0;
        }

        for (uint32_t bar = 0; bar < bars; bar++) {
            uint32_t ph = bar % 4u, b0 = bar * 16u;
            int32_t chord = (int32_t)dice_chord_at(b0);
            int32_t shift = ph == 1u && bar ?
                            (int32_t)dice_chord_at(b0) -
                            (int32_t)dice_chord_at(b0 - 16u) : 0;

            if (bar == bars - 1u && bars >= 2u) {
                uint32_t h = (k + 1u) / 2u;
                uint32_t land;

                for (j = 0; j < h; j++) {
                    int32_t note = dice_note(t, base,
                        at[j] % 4u == 0u ?
                        dice_near_chord(degree[j] + shift, chord) :
                        degree[j] + shift);

                    dice_step_note(&t->step[b0 + at[j]], &note, 1u,
                                   at[j] % 4u == 0u ? 96u : 84u, 0u);
                }

                land = b0 + (h < k && at[h] > 8u ? at[h] : 8u);
                if (land > b0 + at[h - 1u] && land < len) {
                    int32_t note = dice_note(t, base,
                                             dice_near_chord(0, chord));
                    dice_step_note(&t->step[land], &note, 1u, 90u, 0u);
                    dice_hold(t, land, len - land - 1u, len);
                }
                continue;
            }

            if (ph == 2u && dice_chance(30))
                continue;

            for (j = 0; j < k; j++) {
                int32_t dd = degree[j] + shift;
                uint32_t pos = b0 + at[j];
                uint32_t next, gap;
                int32_t note;

                if (pos >= len)
                    break;
                if (ph == 2u && j == k - 1u)
                    dd += dice_chance(50) ? 1 : -1;
                if (at[j] % 4u == 0u)
                    dd = dice_near_chord(dd, chord);

                note = dice_note(t, base, dd);
                if (note > 79)
                    note -= 12;
                dice_step_note(&t->step[pos], &note, 1u,
                               at[j] % 4u == 0u ? 96u : 82u,
                               dice_chance(10) ? SF_SLIDE : 0u);

                next = j + 1u < k ? at[j + 1u] : 16u + at[0];
                gap = next - at[j];
                if (gap > 2u + (2u - dice_piece.energy))
                    dice_hold(t, pos, gap - 2u - (2u - dice_piece.energy), len);
            }
        }
    }
}

static void dice_arp(track_t *t, uint32_t len)
{
    const dice_style_t *st = dice_piece.style;
    int32_t tonic = 50, chord[4];
    uint32_t energy = dice_piece.energy;
    uint32_t rate = energy == 2u || st->arp == DICE_ARP_GLASS ? 1u : 2u;
    uint32_t hits = (uint32_t)dice_rr(5, 9) + energy * 2u;
    uint32_t walk = 0;
    static const uint8_t ALB[4] = {0, 3, 1, 3};

    if (st->arp == DICE_ARP_GLASS || st->arp == DICE_ARP_PULSE)
        hits = 16u;

    dice_piece.last_n = 0;
    for (uint32_t i = 0; i < len; i++) {
        uint32_t idx, j = 0;
        int32_t note;

        if (i % rate)
            continue;
        idx = i / rate;
        if (!dice_euclid(idx % 16u, hits, 16u, 0u) && dice_chance(80))
            continue;

        if (i % dice_piece.chord_steps == 0u || !dice_piece.last_n) {
            dice_chord(t, tonic + 2, (int32_t)dice_chord_at(i),
                       dice_piece.style->voicing, chord);
        } else {
            for (j = 0; j < 4u; j++)
                chord[j] = dice_piece.last[j];
        }

        switch (st->arp) {
        case DICE_ARP_ALBERTI:
            j = ALB[idx % 4u];
            break;
        case DICE_ARP_GLASS: {
            uint32_t group = (idx / 8u) % 2u ? 5u : 3u;
            j = (idx % group) % 4u;
            break;
        }
        case DICE_ARP_PULSE:
            j = idx % 8u == 7u ? 2u : 0u;
            break;
        case DICE_ARP_WALK:
            walk = (walk + (dice_chance(50) ? 1u : 3u)) % 4u;
            j = walk;
            break;
        default:
            j = (idx % 6u) < 4u ? idx % 6u : 6u - idx % 6u;
            break;
        }

        note = chord[j];
        while (note > 72)
            note -= 12;
        while (note < 48)
            note += 12;
        dice_step_note(&t->step[i], &note, 1u,
                       idx % 4u == 0u ? 92u :
                       st->arp == DICE_ARP_PULSE ? 70u : 78u, 0u);
    }
}

static void dice_texture(track_t *t, uint32_t len)
{
    for (uint32_t i = 0; i < len; i += 16u) {
        uint32_t at = i + (uint32_t)dice_rr(0, 2) * 4u;
        int32_t degree = dice_chance(30) ? 4 :
                         dice_chance(30) ? 1 : 0;
        int32_t note;

        if (i && dice_chance(45))
            continue;
        note = dice_note(t, 43, degree);
        dice_step_note(&t->step[at < len ? at : i], &note, 1u, 72u, 0u);
    }

    for (uint32_t i = 0; i < len; i++)
        if (t->step[i].time == ST_NOTE)
            dice_hold(t, i, 11u, len);
}

/* Infer a musical role from the existing instrument, without changing its engine. */
static uint32_t dice_track_role(const track_t *t)
{
    const engine_t *e;
    uint32_t tag;

    if (drum_track(t))
        return DICE_DRUM;

    e = ENGINES[eng_idx(t->eng_req)];
    if (!e->npresets || t->preset >= e->npresets)
        return DICE_ROLE_N;

    tag = e->presets[t->preset].tag;
    if (tag == PT_BASS)
        return DICE_BASS;
    if (tag == PT_PAD)
        return DICE_PAD;
    if (tag == PT_PLUCK || tag == PT_KEYS)
        return DICE_ARP;
    if (tag == PT_FX)
        return DICE_TEX;
    if (tag == PT_LEAD)
        return DICE_LEAD;
    return DICE_ROLE_N;
}

/* Choose a factory preset of the requested role, in the track's existing engine.
 * Preserve the track's four FX sends around the preset load. */
/* Tags de presets autorisés pour chaque rôle.
 * PT_NONE est un tag valide : il permet aussi de sélectionner des presets
 * qui n'ont pas de tag de rôle particulier. */
typedef struct {
    uint8_t count;
    uint8_t tag[3];
} dice_tag_set_t;

static const dice_tag_set_t DICE_ROLE_TAGS[DICE_ROLE_N] = {
    [DICE_DRUM] = {1, {PT_DRUM}},
    [DICE_BASS] = {1, {PT_BASS}},
    [DICE_PAD]  = {1, {PT_PAD}},
    [DICE_LEAD] = {2, {PT_LEAD, PT_KEYS}},
    [DICE_ARP]  = {3, {PT_NONE, PT_PLUCK, PT_KEYS}},
    [DICE_TEX]  = {2, {PT_FX, PT_PAD}},
};

static int dice_role_has_tag(uint32_t role, uint32_t tag)
{
    const dice_tag_set_t *set;

    if (role >= DICE_ROLE_N)
        return 0;

    set = &DICE_ROLE_TAGS[role];
    for (uint32_t i = 0; i < set->count; i++)
        if (set->tag[i] == tag)
            return 1;

    return 0;
}

/* Choose uniformly from matching factory presets in the track's existing
 * engine. Preserve its four FX sends around apply_preset_to(). */
static void dice_preset_for_role(track_t *t, uint32_t role)
{
    const engine_t *e = ENGINES[eng_idx(t->eng_req)];
    uint32_t count = 0, pick;
    int16_t sends[4];

    if (role >= DICE_ROLE_N || !e->npresets)
        return;

    for (uint32_t i = 0; i < e->npresets; i++)
        count += dice_role_has_tag(role, e->presets[i].tag);

    if (!count)
        return;

    pick = rng() % count;
    for (uint32_t i = 0; i < e->npresets; i++) {
        if (!dice_role_has_tag(role, e->presets[i].tag))
            continue;

        if (!pick--) {
            for (uint32_t k = 0; k < 4u; k++)
                sends[k] = t->p[P_DIST + k];

            apply_preset_to(t, i);

            for (uint32_t k = 0; k < 4u; k++)
                t->p[P_DIST + k] = sends[k];

            return;
        }
    }
}

static uint32_t dice_fallback_role(uint32_t melodic_index)
{
    return dice_piece.style->prio[melodic_index % 5u];
}

static void dice_generate_track(track_t *t, uint32_t role)
{
    track_defaults_steps(t);
    t->p[P_SLEN] = NSTEP;

    if (role == DICE_DRUM) {
        dice_drums(t, NSTEP);
        return;
    }

    switch (role) {
    case DICE_BASS:
        dice_bass(t, NSTEP);
        break;
    case DICE_PAD:
        dice_pads(t, NSTEP);
        break;
    case DICE_ARP:
        dice_arp(t, NSTEP);
        break;
    case DICE_TEX:
        dice_texture(t, NSTEP);
        break;
    default:
        dice_lead(t, NSTEP);
        break;
    }
}

/* Return a message for tl_do(); that handler is responsible for normal UI feedback. */
static const char *dice_all_tracks(void)
{
    const dice_style_t *st;
    uint32_t melodic_index = 0;

    if (transport_busy()) {
        ui_message("STOP TO DICE");
        return 0;
    }

    st = &DICE_STYLES[rng() % DICE_NSTYLE];

    dice_piece.style = st;
    dice_piece.progression = rng() % 3u;
    dice_piece.scale = st->scale[rng() % 4u];
    dice_piece.root = rng() % 12u;
    dice_piece.energy = (uint32_t)dice_rr(st->energy_lo, st->energy_hi);
    dice_piece.chord_steps = 16u * st->bars;

    if (st->prog[dice_piece.progression][0] == 127)
        dice_piece.progression = 0u;
    for (dice_piece.progression_n = 0;
         dice_piece.progression_n < 4u &&
         st->prog[dice_piece.progression][dice_piece.progression_n] != 127;
         dice_piece.progression_n++)
        ;
    if (!dice_piece.progression_n)
        dice_piece.progression_n = 1u;
    if (dice_piece.chord_steps > NSTEP)
        dice_piece.chord_steps = NSTEP;

    /* Snapshot the selected track first, then each other track. */
    for (uint32_t n = 0; n < NTRK; n++) {
        uint32_t k = (song.sel + n) % NTRK;
        track_t *t = &trk[k];
        uint32_t role = dice_track_role(t);

        if (role == DICE_ROLE_N)
            role = dice_fallback_role(melodic_index);
        if (role != DICE_DRUM)
            melodic_index++;

        /* No engine change; if the engine has no matching tag, its sound stays. */
        dice_preset_for_role(t, role);
        tl_undo_take(t, "DICED SONG");

        dice_piece.last_n = 0;
        dice_generate_track(t, role);
    }

    return "DICED 6 PATTERNS";
}