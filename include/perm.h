#pragma once

// 0ABC
// 0: Préfixe de notation octale
// A: Permission du propriétaire
// B: Permission du groupe
// C: Permission des autres

// 0: Aucune permission (---)
// 1: Permission d'exécution (--x)
// 2: Permission d'écriture (-w-)
// 3: Permission d'écriture et d'exécution (-wx)
// 4: Permission de lecture (r--)
// 5: Permission de lecture et d'exécution (r-x)
// 6: Permission de lecture et d'écriture (rw-)
// 7: Toutes les permissions (rwx)

/* 0755 */
#define DEFAULT_MODE 0755
